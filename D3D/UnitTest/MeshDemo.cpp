#include "stdafx.h"
#include "MeshDemo.h"

void MeshDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(20, 0, 0);
	Context::Get()->GetCamera()->Position(1, 36, -85);
	((Freedom*)Context::Get()->GetCamera())->Speed(50, 2);

	shader = new Shader(L"11_Mesh.fxo");

	CreateMesh();
}

void MeshDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(quad);
	//SafeDelete(plane);
}

void MeshDemo::Update()
{
	static Vector3 lightDirection = Vector3(-1, -1, 1);
	ImGui::SliderFloat3("Light Direction", lightDirection, -1, 1);
	shader->AsVector("LightDirection")->SetFloatVector(lightDirection);

	quad->Update();
	//plane->Update();
}

void MeshDemo::Render()
{
	quad->Render();
	//plane->Render();
}

void MeshDemo::CreateMesh()
{
	quad = new MeshQuad(shader);
	quad->DiffuseMap(L"Box.png");
	//quad->Pass(1);

	/*plane = new MeshPlane(shader, 2.5f, 2.5f);
	plane->Scale(12, 1, 12);
	plane->DiffuseMap(L"Floor.png");*/
	//plane->Pass(1);
}
