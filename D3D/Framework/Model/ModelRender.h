#pragma once

class ModelRender
{
public:
	ModelRender(Shader* shader);
	~ModelRender();

	void Update();
	void Render();

public:
	void ReadMesh(wstring file);
	void ReadMaterial(wstring file);

	Transform* GetTransform() { return transform; }
	Model* GetModel() { return model; }

	void Pass(UINT pass);

private:
	//*.mesh 파일에서 읽어온 bones의 matrix를 ModelMesh::boneBuffer로 복사
	void UpdateTransforms();

private:
	bool bRead = false;

	Shader* shader;
	Model* model;

	Transform* transform; //Actor Transform(WS)

	Matrix transforms[MAX_MODEL_TRANSFORMS]; //Bone Transform(BS)
};
