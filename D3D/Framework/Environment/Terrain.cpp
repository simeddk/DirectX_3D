#include "Framework.h"
#include "Terrain.h"

Terrain::Terrain(Shader* shader, wstring heightMapPath)
	: shader(shader)
{
	heightMap = new Texture(heightMapPath);

	CreateVertexData();
	CreateIndexData();
	CreateNormalData();
	CreateBuffer();

	D3DXMatrixIdentity(&world);
}

Terrain::~Terrain()
{
	SafeDeleteArray(vertices);
	SafeRelease(vertexBuffer);

	SafeDeleteArray(indices);
	SafeRelease(indexBuffer);

	SafeDelete(heightMap);
}

void Terrain::Update()
{
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void Terrain::Render()
{
	VisibleNormal();

	if (baseMap != nullptr)
		shader->AsSRV("BaseMap")->SetResource(baseMap->SRV());

	UINT stride = sizeof(VertexTerrain);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->DrawIndexed(0, pass, indexCount);
}

void Terrain::VisibleNormal()
{
	static bool bVisibleNormal = false;
	static int interval = 3;
	ImGui::Checkbox("Visble Normal", &bVisibleNormal);
	ImGui::SliderInt("Interval", &interval, 1, 5);

	if (bVisibleNormal)
	{
		for (UINT z = 0; z < height; z += interval)
		{
			for (UINT x = 0; x < width; x += interval)
			{
				UINT index = width * z + x;

				Vector3 start = vertices[index].Position;
				Vector3 end = start + vertices[index].Normal;
				DebugLine::Get()->RenderLine(start, end);
			}
		}
	}
}

void Terrain::BaseMap(wstring path)
{
	SafeDelete(baseMap);

	baseMap = new Texture(path);
}

void Terrain::CreateVertexData()
{
	width = heightMap->GetWidth();
	height = heightMap->GetHeight();

	vector<Color> pixels;
	heightMap->ReadPixel(&pixels);

	vertexCount = width * height;
	vertices = new VertexTerrain[vertexCount];

	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width; x++)
		{
			UINT index = width * y + x;
			UINT reverse = width * (height - y - 1) + x;

			vertices[index].Position.x = (float)x;
			vertices[index].Position.y = pixels[reverse].r * 255.f / 10.f;
			vertices[index].Position.z = (float)y;

			vertices[index].Uv.x = x / (float)width - 1;
			vertices[index].Uv.y = 1.f - (y / (float)(height - 1));
		}
	}
}

void Terrain::CreateIndexData()
{
	indexCount = (width - 1) * (height - 1) * 6;
	indices = new UINT[indexCount];

	UINT index = 0;
	for (UINT y = 0; y < height - 1; y++)
	{
		for (UINT x = 0; x < width - 1; x++)
		{
			indices[index + 0] = width * y + x;
			indices[index + 1] = width * (y + 1) + x;
			indices[index + 2] = width * y + (x + 1);
			indices[index + 3] = width * y + (x + 1);
			indices[index + 4] = width * (y + 1) + x;
			indices[index + 5] = width * (y + 1) + (x + 1);

			index += 6;
		}
	}
}

void Terrain::CreateNormalData()
{
	for (UINT i = 0; i < indexCount / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		VertexTerrain v0 = vertices[index0];
		VertexTerrain v1 = vertices[index1];
		VertexTerrain v2 = vertices[index2];

		Vector3 e1 = v1.Position - v0.Position;
		Vector3 e2 = v2.Position - v0.Position;

		Vector3 normal;
		D3DXVec3Cross(&normal, &e1, &e2);
		D3DXVec3Normalize(&normal, &normal);
		
		vertices[index0].Normal += normal;
		vertices[index1].Normal += normal;
		vertices[index2].Normal += normal;
	}

	for (UINT i = 0; i < vertexCount; i++)
		D3DXVec3Normalize(&vertices[i].Normal, &vertices[i].Normal);
}

void Terrain::CreateBuffer()
{
	//Create VerexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(VertexTerrain) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	//Create IndexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * indexCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}
}
