Texture2DArray<float4> Input;
RWTexture2DArray<float4> Output;


[numthreads(32, 32, 1)]
void CS_Diffuse(uint3 id : SV_DispatchThreadID)
{
	Output[id] = Input.Load(int4(id, 0));
}

[numthreads(32, 32, 1)]
void CS_Inverse(uint3 id : SV_DispatchThreadID)
{
	Output[id] = 1 - Input.Load(int4(id, 0));
}

[numthreads(32, 32, 1)]
void CS_RedChannel(uint3 id : SV_DispatchThreadID)
{
	float4 input = Input.Load(int4(id, 0));
	
	Output[id] = float4(input.r, 0, 0, 1);
}

[numthreads(32, 32, 1)]
void CS_Grayscale(uint3 id : SV_DispatchThreadID)
{
	float4 input = Input.Load(int4(id, 0));
	
	Output[id] = (input.r + input.g + input.b) * 0.333333f;
}


technique11 T0
{
	pass P0
	{
		SetVertexShader(NULL);
		SetPixelShader(NULL);

		SetComputeShader(CompileShader(cs_5_0, CS_Diffuse()));
	}

	pass P1
	{
		SetVertexShader(NULL);
		SetPixelShader(NULL);

		SetComputeShader(CompileShader(cs_5_0, CS_Inverse()));
	}

	pass P2
	{
		SetVertexShader(NULL);
		SetPixelShader(NULL);

		SetComputeShader(CompileShader(cs_5_0, CS_RedChannel()));
	}

	pass P3
	{
		SetVertexShader(NULL);
		SetPixelShader(NULL);

		SetComputeShader(CompileShader(cs_5_0, CS_Grayscale()));
	}
}