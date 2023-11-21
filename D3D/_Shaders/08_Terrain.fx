matrix World;
matrix View;
matrix Projection;

struct VertexInput
{
	float4 Position : Position;
};

struct VertexOutput
{
	float4 Position : SV_Position;
};

RasterizerState FillMode_WireFrame
{
	FillMode = WIREFRAME;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;
	output.Position = mul(input.Position, World);
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);
	
	return output;
}

float4 PS(VertexOutput input) : SV_Target
{
	return float4(1, 1, 1, 1);
}


//GetHeight
struct VertexOutput_HeightColor
{
	float4 Position : SV_Position;
	float3 wPosition : Position1;
	float4 Color : Color;
};

float4 GetHeightColor(float y)
{
	if (y > 20.f)
		return float4(1, 1, 1, 1);
	
	if (y > 10.f)
		return float4(0, 1, 0, 1);
	
	if (y > 5.f)
		return float4(0, 0, 1, 1);
	
	return float4(1, 1, 1, 1);
}

VertexOutput_HeightColor VS_HeightColor(VertexInput input)
{
	VertexOutput_HeightColor output;
	output.Position = mul(input.Position, World);
	output.wPosition = output.Position.xyz;
	
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);
	
	return output;
}

float4 PS_HeightColor(VertexOutput_HeightColor input) : SV_Target
{
	return GetHeightColor(input.wPosition.y);
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
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}

	pass P2
	{
		SetVertexShader(CompileShader(vs_5_0, VS_HeightColor()));
		SetPixelShader(CompileShader(ps_5_0, PS_HeightColor()));
	}

	
}