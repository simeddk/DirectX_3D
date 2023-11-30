#pragma once

#include "stdafx.h"

struct asBone
{
	int Index;
	string Name;

	int Parent;
	Matrix Transform;
};

struct asMeshPart
{
	//Todo. 머티리얼을 기준으로 또 나눠지겠군...
};

struct asMesh
{
	int BoneIndex;

	vector<Model::VertexModel> Vertices;
	vector<UINT> Indices;
};