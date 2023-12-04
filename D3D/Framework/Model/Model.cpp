#include "Framework.h"
#include "Model.h"
#include "Utilities/BinaryFile.h"

Model::Model()
{

}

Model::~Model()
{
}

void Model::ReadMesh(wstring file)
{
	file = L"../../_Models/" + file + L".mesh";

	BinaryReader* r = new BinaryReader(file);
	
	UINT count = 0;

	//Read Bone
	count = r->UInt();
	for (UINT i = 0; i < count; i++)
	{
		ModelBone* bone = new ModelBone();
		
		bone->index = r->Int();
		bone->name = String::ToWString(r->String());
		bone->parentIndex = r->Int();
		bone->transform = r->Matrix();

		bones.push_back(bone);
	}

	//Read Mesh
	count = r->UInt();
	for (UINT i = 0 ; i < count; i++)
	{
		ModelMesh* mesh = new ModelMesh();

		mesh->boneIndex = r->UInt();

		//Vertx Data
		{
			//Todo. 내일 다시 설명...
			UINT count = r->UInt();

			vector<Model::VertexModel> vertices;
			vertices.assign(count, Model::VertexModel());

			//
			void* ptr = (void*)&(vertices[0]);
			r->Byte((void**)&mesh->vertices, );

			//mesh->vertexCount = count;
		}
		
	}

}

void Model::BindBone()
{
}

void Model::BindMesh()
{
}
