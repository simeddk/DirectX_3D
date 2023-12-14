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
	ID3D11ShaderResourceView* transformsSRV;
	ID3DX11EffectShaderResourceVariable* sTransformsSRV;

private:
	struct KeyFrameDesc
	{
		int Clip = 0;

		UINT CurrentFrame = 0;
		UINT NextFrame = 0;

		float Time = 0.f; //다음 프레임으로 넘어갈 시간(이 값이 1이 됐을 때)
		float RunningTime; //델타 타임 누적

		float Speed = 1.f;

		Vector2 Padding;
	} keyFrameDesc;

	ConstantBuffer* frameBuffer;
	ID3DX11EffectConstantBuffer* sFrameBuffer;

private:
	Shader* shader;
	Model* model;

	Transform* transform; //Actor Transform(WS)
};