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
	string MaterialName;

	UINT StartVertex;
	UINT VertexCount;
	UINT StartIndex;
	UINT IndexCount;
};

struct asMesh
{
	int BoneIndex;

	vector<Model::VertexModel> Vertices;
	vector<UINT> Indices;

	vector<asMeshPart*> MeshParts;
};

struct asMaterial
{
	string Name;

	Color Ambient;
	Color Diffuse;
	Color Specular;
	Color Emissive;

	string DiffuseFile;
	string SpecularFile;
	string NormalFile;
};

//1 Bone, 1 Frame
struct asKeyFrameData
{
	float Frame;

	Vector3 Scale;
	Quaternion Rotation;
	Vector3 Translation;
};

//1 Bone, All Frame
struct asKeyFrame
{
	string BoneName;
	vector<asKeyFrameData> Transforms;
};

//All Bone, All Frame(Final)
struct asClip
{
	string Name;

	UINT FrameCount;
	float FrameRate;

	vector<asKeyFrame*> Keyframes;
};

//All Bone, All Frame(Temp)
struct asClipNode
{
	aiString Name;
	vector<asKeyFrameData> keyframe;
};