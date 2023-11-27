#pragma once

class Terrain
{
public:
	Terrain(Shader* shader, wstring heightMapPath);
	~Terrain();

	void Update();
	void Render();

	void VisibleNormal();

	UINT& Pass() { return pass; }

	void BaseMap(wstring path);

private:
	void CreateVertexData();
	void CreateIndexData();
	void CreateNormalData();

private:
	struct VertexTerrain
	{
		Vector3 Position = Vector3(0, 0, 0);
		Vector3 Normal = Vector3(0, 1, 0);
		Vector2 Uv = Vector2(0, 0);
	};

private:
	Shader* shader;
	UINT pass = 0;

	UINT width, height;

	UINT vertexCount;
	VertexTerrain* vertices;
	VertexBuffer* vertexBuffer;

	UINT indexCount;
	UINT* indices;
	IndexBuffer* indexBuffer;

	Matrix world;

	Texture* heightMap;
	Texture* baseMap = nullptr;
};