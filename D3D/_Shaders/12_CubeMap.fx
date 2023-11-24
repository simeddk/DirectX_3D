matrix World;
matrix View;
matrix Projection;

float3 LightDirection;

TextureCube CubeMap;

struct VertexInput
{
	float4 Position : Position;
};

struct VertexOutput
{
	float4 Position : SV_Position;
	float3 oPosition : Position1;
};

RasterizerState FillMode_WireFrame
{
	FillMode = WIREFRAME;
};

SamplerState LinearSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;
	
	output.oPosition = input.Position.xyz;
	
	output.Position = mul(input.Position, World);
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);
	
	return output;
}

float4 PS(VertexOutput input) : SV_Target
{
	
	float4 diffuseColor = CubeMap.Sample(LinearSampler, input.oPosition);

	return diffuseColor;
}

float4 PS_WireFrame(VertexOutput input) : SV_Target
{
	return float4(0, 1, 0, 1);
}

technique11 T0
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}

	pass P1
	{
		SetRasterizerState(FillMode_WireFrame);

		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS_WireFrame()));
	}
}