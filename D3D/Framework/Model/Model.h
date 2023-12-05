#pragma once

#define MAX_MODEL_TRANSFORMS 250

class ModelBone;
class ModelMesh;
class ModelMeshPart;

class Model
{
public:
	friend class ModelRender;

private:
	Model();
	~Model();

private:
	//*.mesh 파일 읽어오기
	void ReadMesh(wstring file);

private:
	void BindBone(); //Make Bone Tree
	void BindMesh(); //(1)meshes[i]->Binding() 호출, (2) boneIndex를 Set

public:
	UINT BoneCount() { return bones.size(); }
	vector<ModelBone*>& Bones() { return bones; }
	ModelBone* BoneByIndex(UINT index) { return bones[index]; }
	ModelBone* BoneByName(wstring name);

	UINT MeshCount() { return meshes.size(); }
	vector<ModelMesh*>& Meshes() { return meshes; }
	ModelMesh* MeshByIndex(UINT index) { return meshes[index]; }

public:
	struct VertexModel
	{
		Vector3 Position;
		Vector2 Uv;
		Vector3 Normal;
		Vector3 Tangent;
		Vector4 BlendIndices;
		Vector4 BlendWeights;
	};

private:
	ModelBone* root;

	vector<ModelBone*> bones;
	vector<ModelMesh*> meshes;
};