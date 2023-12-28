#include "Framework.h"
#include "ModelRender.h"

ModelRender::ModelRender(Shader* shader)
	: shader(shader)
{
	model = new Model();

	sTransformsSRV = shader->AsSRV("TransformsMap");

	instanceWorldBuffer = new VertexBuffer(worlds, MAX_MODEL_INSTANCE, sizeof(Matrix), 1, true);
	instanceColorBuffer = new VertexBuffer(colors, MAX_MODEL_INSTANCE, sizeof(Color), 2, true);
}

ModelRender::~ModelRender()
{
	SafeDelete(model);
	
	SafeDelete(instanceWorldBuffer);
	SafeDelete(instanceColorBuffer);

	SafeDelete(texture);
	SafeDelete(transformsSRV);

	for (Transform* transform : transforms)
		SafeDelete(transform);
}

void ModelRender::Update()
{
	if (texture == nullptr)
	{
		for (ModelMesh* mesh : model->meshes)
			mesh->SetShader(shader);

		CreateTexture();
	}

	for (ModelMesh* mesh : model->meshes)
		mesh->Update();
}

void ModelRender::Render()
{
	for (ModelMesh* mesh : model->meshes)
	{
		mesh->SetTransform(transform);
		mesh->Render();
	}
}

void ModelRender::ReadMesh(wstring file)
{
	model->ReadMesh(file);
}

void ModelRender::ReadMaterial(wstring file)
{
	bRead = true;

	model->ReadMaterial(file);
}

void ModelRender::Pass(UINT pass)
{
	for (ModelMesh* mesh : model->Meshes())
		mesh->Pass(pass);
}

void ModelRender::CreateTexture()
{
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = MAX_MODEL_TRANSFORMS * 4;
	desc.Height = MAX_MODEL_INSTANCE;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;

	Matrix bones[MAX_MODEL_TRANSFORMS];
	for (UINT i = 0; i < MAX_MODEL_INSTANCE; i++)
	{
		for (UINT b = 0; b < model->BoneCount(); b++)
		{
			//MeshBone을 얻어와서 역행렬을 건다
			ModelBone* bone = model->BoneByIndex(b);

			//ParentBone을 가져온다
			Matrix parent;
			int parentIndex = bone->ParentIndex();
			if (parentIndex < 0)
				D3DXMatrixIdentity(&parent);
			else
				parent = bones[parentIndex];

			//Todo.
			Matrix animation;

			ModelKeyFrame* frame = clip->Keyframe(bone->Name());

			if (frame != nullptr)
			{
				ModelKeyFrameData& data = frame->Transforms[f];

				Matrix S, R, T;
				D3DXMatrixScaling(&S, data.Scale.x, data.Scale.y, data.Scale.z);
				D3DXMatrixRotationQuaternion(&R, &data.Rotation);
				D3DXMatrixTranslation(&T, data.Translation.x, data.Translation.y, data.Translation.z);

				animation = S * R * T;
			}
			else
			{
				D3DXMatrixIdentity(&animation);
			}

			bones[b] = animation * parent;
			clipTransform[index].Trasnform[f][b] = inv * bones[b];
			//-> (inv * animation) * parent;
		}
	}
}

Transform* ModelRender::AddTransform()
{
	return nullptr;
}

void ModelRender::UpdateTransforms()
{
	for (UINT i = 0; i < model->BoneCount(); i++)
	{
		ModelBone* bone = model->BoneByIndex(i);
		transforms[i] = bone->Transform();
	}

	for (ModelMesh* mesh : model->Meshes())
		mesh->Transforms(transforms);
}

void ModelRender::SetColor(UINT instance, Color& color)
{
}
