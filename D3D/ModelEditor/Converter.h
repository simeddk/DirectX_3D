#pragma once

class Converter
{
public:
	Converter();
	~Converter();

	//fbx ���� �о����
	void ReadFile(wstring file);

	//scene�� meshes, bones ������ *.mesh
public:
	void ExportMesh(wstring savePath);

private:
	void ReadBoneData(aiNode* node, int index, int parent);
	void ReadMeshData(aiNode* node, int index);
	void WriteMeshData(wstring savePath);

	//scene�� maetrial ������ *.material(xml)
public:
	void ExportMaterial(wstring savePath, bool bOverWrite = true);

private:
	void ReadMaterialData();
	bool FoundMaterialData(aiMaterial* material);
	void WriteMaterialData(wstring savePath);
	string WriteTexture(string saveFolder, string file);

	//(Animation.fbx)scene�� Clipo ������ *.clip
public:
	void ExportAnimClip(UINT index, wstring savePath);

private:
	struct asClip* ReadClipData(aiAnimation* animation); //Keyframe ����
	void ReadKeyframeData(struct asClip* clip, aiNode* node, vector<struct asClipNode>& aniNodeInfos); //Retarget
	void WriteClipData(struct asClip* clip, wstring savePath);

private:

private:
	wstring file;

	Assimp::Importer* importer;
	const aiScene* scene;

	vector<struct asBone*> bones;
	vector<struct asMesh*> meshes;
	vector<struct asMaterial*> materials;
};