#include "stdafx.h"
#include "AnimationDemo.h"
#include "Converter.h"

void AnimationDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(12, 0, 0);
	Context::Get()->GetCamera()->Position(2, 4, -12);

	shader = new Shader(L"15_Animation.fxo");
	
	Kachujin();

	sky = new CubeSky(L"Environment/GrassCube1024.dds");
	sky->Pass(2);

	planeShader = new Shader(L"11_Mesh.fxo");
	plane = new MeshPlane(planeShader, 6, 6);
	plane->GetTransform()->Scale(12, 1, 12);
	plane->DiffuseMap(L"Floor.png");
}

void AnimationDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(kachujin);

	SafeDelete(sky);
	SafeDelete(planeShader);
	SafeDelete(plane);
}

void AnimationDemo::Update()
{
	//Test
	static int clip = 0;
	static float speed = 1.f;
	static float takeTime = 1.f;

	ImGui::InputInt("Clip", &clip);
	clip = Math::Clamp(clip, 0, 4);

	ImGui::SliderFloat("Speed", &speed, 0.1f, 5.f);
	ImGui::SliderFloat("TakeTime", &takeTime, 0.1f, 5.f);

	if (ImGui::Button("Apply"))
		kachujin->PlayTweenMode(clip, speed, takeTime);


	static Vector3 LightDirection = Vector3(-1, -1, +1);
	ImGui::SliderFloat3("LightDirection", LightDirection, -1, +1);
	shader->AsVector("LightDirection")->SetFloatVector(LightDirection);
	planeShader->AsVector("LightDirection")->SetFloatVector(LightDirection);

	static UINT pass = 0;
	ImGui::InputInt("Pass", (int*)&pass);
	pass %= 2;
	
	sky->Update();
	plane->Update();

	if (kachujin != nullptr)
	{
		kachujin->Pass(pass);
		kachujin->Update();
	}

}

void AnimationDemo::Render()
{
	sky->Render();
	plane->Render();

	if (kachujin != nullptr)
		kachujin->Render();

}

void AnimationDemo::Kachujin()
{
	kachujin = new ModelAnimator(shader);
	kachujin->ReadMesh(L"Kachujin/Mesh");
	kachujin->ReadMaterial(L"Kachujin/Mesh");
	
	kachujin->ReadClip(L"Kachujin/Idle");
	kachujin->ReadClip(L"Kachujin/Walk");
	kachujin->ReadClip(L"Kachujin/Run");
	kachujin->ReadClip(L"Kachujin/Slash");
	kachujin->ReadClip(L"Kachujin/Uprock");

	kachujin->GetTransform()->Position(5, 0, 0);
	kachujin->GetTransform()->Scale(0.01f, 0.01f, 0.01f);
}

