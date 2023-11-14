#include "stdafx.h"
#include "WorldDemo.h"

void WorldDemo::Initialize()
{
	shader = new Shader(L"04_World.fxo");

	//Polygon
	{
		vertices[0].Position = Vector3(-0.5f, -0.5f, +0.0f);
		vertices[1].Position = Vector3(-0.5f, +0.5f, +0.0f);
		vertices[2].Position = Vector3(+0.5f, -0.5f, +0.0f);
		vertices[3].Position = Vector3(+0.5f, -0.5f, +0.0f);
		vertices[4].Position = Vector3(-0.5f, +0.5f, +0.0f);
		vertices[5].Position = Vector3(+0.5f, +0.5f, +0.0f);

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertices);
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	D3DXMatrixIdentity(&world);
}

void WorldDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

void WorldDemo::Update()
{
	// x 위치 : world._41
	// y 위치 : world._42
	// z 위치 : world._43

	if (Keyboard::Get()->Press('D'))
		world._41 += 2.f * Time::Delta();
	else if (Keyboard::Get()->Press('A'))
		world._41 -= 2.f * Time::Delta();

	if (Keyboard::Get()->Press('W'))
		world._42 += 2.f * Time::Delta();
	else if (Keyboard::Get()->Press('S'))
		world._42 -= 2.f * Time::Delta();

	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void WorldDemo::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	static bool bWireFrame;
	ImGui::Checkbox("WireFrame", &bWireFrame);

	shader->Draw(0, bWireFrame ? 1 : 0, 6);
}
