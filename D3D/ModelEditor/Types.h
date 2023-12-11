#pragma once

#include "stdafx.h"

//-----------------------------------------------------------------------------
//Mesh
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
//Material
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
//Animation
//-----------------------------------------------------------------------------
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

//1 Bone, All Frame(Temp)
struct asClipNode
{
	aiString Name; //animBone Name
	vector<asKeyFrameData> Keyframe;
};

//-----------------------------------------------------------------------------
//Skinning
//-----------------------------------------------------------------------------
struct asBlendWeight
{
	Vector4 Indices = Vector4(0, 0, 0, 0);
	Vector4 Weights = Vector4(0, 0, 0, 0);

	void Set(UINT iterator, UINT boneIndex, float weight)
	{
		float i = (float)boneIndex;
		float w = weight;

		//Todo. 
		switch (iterator)
		{
			case 0 : Indices.x = 
		}
	}
};

struct asBoneWeights
{
private:
	typedef pair<int, float> Pair;
	vector<Pair> BoneWeigths; //BoneIndex, BoneWeihgt
};