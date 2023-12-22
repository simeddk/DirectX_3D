#include "stdafx.h"
#include "TextureBufferDemo.h"
#include "Objects/Canvas.h"

void TextureBufferDemo::Initialize()
{
	shader = new Shader(L"17_TextureBuffer.fxo");
	
	inputTexture = new Texture(L"Environment/Compute.png");

	textureBuffer = new TextureBuffer(inputTexture->GetTexture());
	shader->AsSRV("Input")->SetResource(textureBuffer->SRV());
	shader->AsUAV("Output")->SetUnorderedAccessView(textureBuffer->UAV());

	canvas = new Canvas();
	canvas->GetTransform()->Scale(D3D::Width(), D3D::Height(), 1);
	canvas->GetTransform()->Position(D3D::Width() * 0.5f, D3D::Height() * 0.5f, 0.f);
	canvas->SRV(textureBuffer->OutputSRV());
}

void TextureBufferDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(inputTexture);
	SafeDelete(textureBuffer);
	SafeDelete(canvas);
}

void TextureBufferDemo::Update()
{
	UINT width = textureBuffer->Width();
	UINT height = textureBuffer->Height();

	float x = width / 32;
	float y = height / 32;

	UINT groupX = (UINT)floorf(x);
	UINT groupY = (UINT)floorf(y);

	//shader->Dispatch(0, 0, groupX, groupY, 1);

	if (ImGui::Button("Diffuse"))
		shader->Dispatch(0, 0, groupX, groupY, 1);

	if (ImGui::Button("Inverse"))
		shader->Dispatch(0, 1, groupX, groupY, 1);

	if (ImGui::Button("RedChannel"))
		shader->Dispatch(0, 2, groupX, groupY, 1);

	if (ImGui::Button("GrayScale"))
		shader->Dispatch(0, 3, groupX, groupY, 1);

	canvas->Update();
}

void TextureBufferDemo::Render()
{
	canvas->Render();
}
