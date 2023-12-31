#include "stdafx.h"
#include "Main.h"
#include "Systems/Window.h"

#include "VertexLineDemo.h"
#include "VertexLineColorDemo.h"
#include "VertexTopologyDemo.h"
#include "PolygonDemo.h"
#include "PlaneDemo.h"
#include "WorldDemo.h"
#include "IndexBufferDemo.h"
#include "GridDemo.h"
#include "TextureDemo.h"
#include "SamplerStateDemo.h"
#include "TerrainDemo.h"
#include "MeshDemo.h"
#include "CubeMapDemo.h"
#include "ThreadDemo.h"
#include "RawBufferDemo.h"
#include "TextureBufferDemo.h"
#include "InstancingDemo.h"

void Main::Initialize()
{
	Push(new InstancingDemo());
}


void Main::Destroy()
{
	for (IExecute* exe : executes)
	{
		exe->Destroy();
		SafeDelete(exe);
	}
}

void Main::Update()
{
	for (IExecute* exe : executes)
		exe->Update();
}

void Main::PreRender()
{
	for (IExecute* exe : executes)
		exe->PreRender();
}

void Main::Render()
{
	for (IExecute* exe : executes)
		exe->Render();
}

void Main::PostRender()
{
	for (IExecute* exe : executes)
		exe->PostRender();
}

void Main::ResizeScreen()
{
	for (IExecute* exe : executes)
		exe->ResizeScreen();
}

void Main::Push(IExecute * execute)
{
	executes.push_back(execute);

	execute->Initialize();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	D3DDesc desc;
	desc.AppName = L"D3D Game";
	desc.Instance = instance;
	desc.bFullScreen = false;
	desc.bVsync = false;
	desc.Handle = NULL;
	desc.Width = 1280;
	desc.Height = 720;
	desc.Background = Color(0.3f, 0.3f, 0.3f, 1.0f);
	D3D::SetDesc(desc);

	Main* main = new Main();
	WPARAM wParam = Window::Run(main);

	SafeDelete(main);

	return wParam;
}