#pragma once

class MeshPlane : public Mesh
{
public:
	MeshPlane(Shader* shader, float tileU  = 1.f, float tileV = 1.f);
	~MeshPlane();

private:
	void Create() override;

	float tileU, tileV;
};