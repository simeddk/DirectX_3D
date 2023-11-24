#include "Framework.h"
#include "CubeMap.h"

CubeMap::CubeMap(Shader* shader)
	: shader(shader)
{
	sSrv = shader->AsSRV("CubeMap");

	mesh = new MeshCube(shader);
}

CubeMap::~CubeMap()
{
	SafeDelete(mesh);

	SafeRelease(srv);
}

void CubeMap::Texture(wstring cubeMapPath)
{
	SafeRelease(srv);

	cubeMapPath = L"../../_Textures/" + cubeMapPath;
	Check(D3DX11CreateShaderResourceViewFromFile
	(
		D3D::GetDevice(),
		cubeMapPath.c_str(),
		nullptr,
		nullptr,
		&srv,
		nullptr
	));
}

void CubeMap::Update()
{
	mesh->Update();
}

void CubeMap::Render()
{
	sSrv->SetResource(srv);

	mesh->Render();
}

void CubeMap::Pass(UINT val)
{
	mesh->Pass(val);
}

void CubeMap::Position(float x, float y, float z)
{
	mesh->Position(x, y, z);
}

void CubeMap::Position(Vector3& vec)
{
	mesh->Position(vec);
}

void CubeMap::Position(Vector3* vec)
{
	mesh->Position(vec);
}

void CubeMap::Rotation(float x, float y, float z)
{
	mesh->Rotation(x, y, z);
}

void CubeMap::Rotation(Vector3& vec)
{
	mesh->Rotation(vec);
}

void CubeMap::Rotation(Vector3* vec)
{
	mesh->Rotation(vec);
}

void CubeMap::RotationDegree(float x, float y, float z)
{
	mesh->RotationDegree(x, y, z);
}

void CubeMap::RotationDegree(Vector3& vec)
{
	mesh->RotationDegree(vec);
}

void CubeMap::RotationDegree(Vector3* vec)
{
	mesh->RotationDegree(vec);
}

void CubeMap::Scale(float x, float y, float z)
{
	mesh->Scale(x, y, z);
}

void CubeMap::Scale(Vector3& vec)
{
	mesh->Scale(vec);
}

void CubeMap::Scale(Vector3* vec)
{
	mesh->Scale(vec);
}