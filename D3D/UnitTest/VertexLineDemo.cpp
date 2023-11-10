#include "stdafx.h"
#include "VertexLineDemo.h"

void VertexLineDemo::Initialize()
{
	shader = new Shader(L"01_Line.fx");

	vertices[0].Position = Vector3(0, 0, 0);
	vertices[0].Position = Vector3(1, 0, 0);

	Device; DeviceContext;
}

void VertexLineDemo::Destroy()
{
}

void VertexLineDemo::Update()
{
}

void VertexLineDemo::Render()
{
}
