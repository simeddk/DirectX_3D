#include "00_Global.fx"
#include "00_Light.fx"

float3 LightDirection = float3(-1, -1, 1);

struct VertexModel
{
	float4 Position : Position;
	float2 Uv : Uv;
	float3 Normal : Normal;
	float3 Tangent : Tangent;
	float4 BlendIndices : BlendIndices;
	float4 BlendWeights : BlendWeights;
};

struct VertexOutput
{
	float4 Position : SV_Position;
	float2 Uv : Uv;
	float3 Normal : Normal;
};

#define MAX_MODEL_TRANSFORMS 250
#define MAX_MODEL_KEYFRAMES 500

cbuffer CB_Bones
{
	Matrix BoneTransforms[MAX_MODEL_TRANSFORMS]; //��ü Bone�� �迭

	uint BoneIndex; //���� ���� �پ���� BoneIndex
};

struct AnimationFrame
{
	int Clip;

	uint CurrentFrame;
	uint NextFrame;

	float Time;
	float RunningTime;

	float Speed;
};

cbuffer CB_KeyFrames
{
	AnimationFrame AnimationFrames;
};

Texture2DArray TransformsMap;

void SetAnimationWorld(inout matrix world, VertexModel input)
{
	float indices[4] = { input.BlendIndices.x, input.BlendIndices.y, input.BlendIndices.z, input.BlendIndices.w };
	float weights[4] = { input.BlendWeights.x, input.BlendWeights.y, input.BlendWeights.z, input.BlendWeights.w };
	
	int clip;
	int currFrame;
	
	clip = AnimationFrames.Clip; //���� ����� Ŭ�� ��ȣ
	currFrame = AnimationFrames.CurrentFrame; //���� ��� ���� ������ ��ȣ
	
	float4 c0, c1, c2, c3;
	
	matrix transform = 0; //Skinning�� ������ ��� ��
	matrix curr = 0; //�ؽ��� �о�� ���� ������� ��Ʈ����

	//Skinning
	[unroll(4)]
	for (int i = 0; i < 4; i++)
	{
		c0 = TransformsMap.Load(int4(indices[i] * 4 + 0, currFrame, clip, 0)); //_11_12_13_14
		c1 = TransformsMap.Load(int4(indices[i] * 4 + 1, currFrame, clip, 0)); //_21_22_23_24
		c2 = TransformsMap.Load(int4(indices[i] * 4 + 2, currFrame, clip, 0)); //_31_32_33_34
		c3 = TransformsMap.Load(int4(indices[i] * 4 + 3, currFrame, clip, 0)); //_41_42_43_44
		
		curr = matrix(c0, c1, c2, c3);
		
		transform += mul(weights[i], curr);
	}
	
	world = mul(transform, world);
	//invMesh * anim * parent (C++) * weight * World (FX)
}

VertexOutput VS(VertexModel input)
{
	VertexOutput output;
	
	SetAnimationWorld(World, input);
	
	output.Position = WorldPosition(input.Position);
	output.Position = ViewProjection(output.Position);
	
	output.Normal = WorldNormal(input.Normal);
	output.Uv = input.Uv;
	
	return output;
}

float4 PS(VertexOutput input) : SV_Target
{
	float3 normal = normalize(input.Normal);
	
	float4 diffuseColor = DiffuseMap.Sample(LinearSampler, input.Uv);
	float lambert = saturate(dot(normal, -LightDirection));

	return diffuseColor * lambert;
}

technique11 T0
{
	P_VP(P0, VS, PS)
	P_RS_VP(P1, FillMode_WireFrame, VS, PS)
}