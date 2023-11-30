#pragma once

class Converter
{
public:
	Converter();
	~Converter();

	//fbx 파일 읽어오기
	void ReadFile(wstring file);

public:
	void ExportMesh(wstring savePath);

private:
	void ReadBoneData(aiNode* node, int index, int parent);
	void ReadMeshData(aiNode* node, int index);
	void WriteMeshData(wstring savePath);

private:
	wstring file;

	Assimp::Importer* importer;
	const aiScene* scene;

	vector<struct asBone*> bones;
	vector<struct asMesh*> meshes;
};