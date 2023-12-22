#pragma once

class Canvas : public Renderer
{
public:
	Canvas();
	~Canvas();

	void Update();
	void Render();

	void SRV(ID3D11ShaderResourceView* srv);

private:
	struct VertexCanvas
	{
		Vector3 Position;
		Vector2 Uv;
	};

private:
	struct Desc
	{
		Matrix View;
		Matrix Projection;
	} desc;

private:
	ConstantBuffer* buffer;
	ID3DX11EffectConstantBuffer* sBuffer;

	ID3DX11EffectShaderResourceVariable* sSrv;
};