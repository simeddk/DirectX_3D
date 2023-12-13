#pragma once

class ModelAnimator
{
public:
	ModelAnimator(Shader* shader);
	~ModelAnimator();

	void Update();
	void Render();

public:
	void ReadMesh(wstring file);
	void ReadMaterial(wstring file);
	void ReadClip(wstring file);

public:
	void SetShader(Shader* shader, bool bDontCreateNewTransform = false);
	void Pass(UINT pass);
	Transform* GetTransform() { return transform; }
	Model* GetModel() { return model; }

private:
	void CreateTexture();
	void CreateClipTransform(UINT index);

private:
	struct ClipTransform
	{
		Matrix** Trasnform;

		ClipTransform()
		{
			Trasnform = new Matrix*[MAX_MODEL_KEYFRAMES];

			for (UINT i = 0; i < MAX_MODEL_KEYFRAMES; i++)
				Trasnform[i] = new Matrix[MAX_MODEL_TRANSFORMS];
		}

		~ClipTransform()
		{
			for (UINT i = 0; i < MAX_MODEL_KEYFRAMES; i++)
				SafeDeleteArray(Trasnform[i]);

			SafeDeleteArray(Trasnform);
		}
	};
	ClipTransform* clipTransform; //clipTransform[c].Trasnform[f][b] = Matrix

private:
	ID3D11Texture2D* texture = nullptr;


private:
	Shader* shader;
	Model* model;

	Transform* transform; //Actor Transform(WS)
};