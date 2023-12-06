#pragma once

class Converter
{
public:
	Converter();
	~Converter();

	//fbx 파일 읽어오기
	void ReadFile(wstring file);

	//scene의 meshes, bones 정보를 *.mesh
public:
	void ExportMesh(wstring savePath);

private:
	void ReadBoneData(aiNode* node, int index, int parent);
	void ReadMeshData(aiNode* node, int index);
	void WriteMeshData(wstring savePath);

	//scene의 maetrial 정보를 *.material(xml)
public:
	void ExportMaterial(wstring savePath, bool bOverWrite = true);

private:
	void ReadMaterialData();
	bool FoundMaterialData(aiMaterial* material);
	void WriteMaterialData(wstring savePath);
	string WriteTexture(string saveFolder, string file);

private:
	wstring file;

	Assimp::Importer* importer;
	const aiScene* scene;

	vector<struct asBone*> bones;
	vector<struct asMesh*> meshes;
	
	vector<struct asMaterial*> materials;
};