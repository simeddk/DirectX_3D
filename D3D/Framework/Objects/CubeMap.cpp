#include "Framework.h"
#include "CubeMap.h"

CubeMap::CubeMap(Shader* shader)
	: shader(shader)
{
	sSrv = shader->AsSRV("CubeMap");

	mesh = new MeshSphere(shader, 0.5f);
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

