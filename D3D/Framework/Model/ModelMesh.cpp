#include "Framework.h"
#include "ModelMesh.h"

//-----------------------------------------------------------------------------
// ModelMesh
// *.mesh의 mesh data를 저장받을 클래스
// VertexBuffer, IndexBuffer 생성
// 모든 Bone의 Matrix를 boneBuffer(cBuffer)로 복사
// Trasnform 객체 생성(Root Bone)
//-----------------------------------------------------------------------------
ModelMesh::ModelMesh()
{
	boneBuffer = new ConstantBuffer(&boneDesc, sizeof(BoneDesc));
}

ModelMesh::~ModelMesh()
{
	SafeDelete(transform);
	SafeDelete(perFrame);

	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);

	SafeDelete(vertexBuffer);
	SafeDelete(indexBuffer);

	SafeDelete(boneBuffer);

	for (ModelMeshPart* part : meshParts)
		SafeDelete(part);
}

void ModelMesh::Binding(Model* model)
{
	vertexBuffer = new VertexBuffer(vertices, vertexCount, sizeof(Model::VertexModel));
	indexBuffer = new IndexBuffer(indices, indexCount);

	for (ModelMeshPart* part : meshParts)
		part->Binding(model);
}

void ModelMesh::Pass(UINT val)
{
	for (ModelMeshPart* part : meshParts)
		part->Pass(val);
}

void ModelMesh::SetShader(Shader* shader)
{
	this->shader = shader;

	SafeDelete(transform);
	transform = new Transform(shader);

	SafeDelete(perFrame);
	perFrame = new PerFrame(shader);

	sBoneBuffer = shader->AsConstantBuffer("CB_Bones");
	
	for (ModelMeshPart* part : meshParts)
		part->SetShader(shader);
}

void ModelMesh::Update()
{
	boneDesc.BoneIndex = boneIndex;

	perFrame->Update();
	transform->Update();

	for (ModelMeshPart* part : meshParts)
		part->Update();
}

void ModelMesh::Render()
{
	boneBuffer->Render();
	sBoneBuffer->SetConstantBuffer(boneBuffer->Buffer());

	perFrame->Render();
	transform->Render();

	vertexBuffer->Render();
	indexBuffer->Render();

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (ModelMeshPart* part : meshParts)
		part->Render();
}

void ModelMesh::Render(UINT drawCount)
{
	boneBuffer->Render();
	sBoneBuffer->SetConstantBuffer(boneBuffer->Buffer());

	perFrame->Render();

	vertexBuffer->Render();
	indexBuffer->Render();

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (ModelMeshPart* part : meshParts)
		part->Render(drawCount);
}

void ModelMesh::Transforms(Matrix* transforms)
{
	memcpy(boneDesc.Transforms, transforms, sizeof(Matrix) * MAX_MODEL_TRANSFORMS);
}

void ModelMesh::SetTransform(Transform* transform)
{
	this->transform->Set(transform);
}

//-----------------------------------------------------------------------------
// ModelMeshPart
// @ 실제 Draw Primitive Call
// @ Material 단위로 구별됨
// @ 딱 자기 부위만 그릴거다
//-----------------------------------------------------------------------------
ModelMeshPart::ModelMeshPart()
{

}

ModelMeshPart::~ModelMeshPart()
{
	SafeDelete(material);
}

void ModelMeshPart::Update()
{
}

void ModelMeshPart::Render()
{
	material->Render();

	shader->DrawIndexed(0, pass, indexCount, startVertex);
}

void ModelMeshPart::Render(UINT drawCount)
{
	material->Render();

	shader->DrawIndexedInstanced(0, pass, indexCount, drawCount, startVertex);
}

void ModelMeshPart::Binding(Model* model)
{
	Material* srcMaterial = model->MaterialByName(materialName);

	material = new Material();
	material->Ambient(srcMaterial->Ambient());
	material->Diffuse(srcMaterial->Diffuse());
	material->Specular(srcMaterial->Specular());
	material->Emissive(srcMaterial->Emissive());

	if (srcMaterial->DiffuseMap() != nullptr)
		material->DiffuseMap(srcMaterial->DiffuseMap()->GetFile());

	if (srcMaterial->SpecularMap() != nullptr)
		material->SpecularMap(srcMaterial->SpecularMap()->GetFile());

	if (srcMaterial->NormalMap() != nullptr)
		material->NormalMap(srcMaterial->NormalMap()->GetFile());
}

void ModelMeshPart::SetShader(Shader* shader)
{
	this->shader = shader;

	material->SetShader(shader);
}
