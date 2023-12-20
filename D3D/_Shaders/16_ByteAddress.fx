RWByteAddressBuffer Output;

struct ComputeInput
{
	uint3 GroupID : SV_GroupID;
	uint3 GroupThreadID : SV_GroupThreadID;
	uint3 DispatchThreadID : SV_DispatchThreadID;
	uint GroupIndex : SV_GroupIndex;
};

struct ComputeOutput
{
	uint3 GroupID;
	uint3 GroupThreadID;
	uint3 DispatchThreadID;
	uint GroupIndex;
};

[numthreads(10, 8, 3)]
void CS(ComputeInput input)
{
	ComputeOutput result;
	result.GroupID = asuint(input.GroupID);
	result.GroupThreadID = asuint(input.GroupThreadID);
	result.DispatchThreadID = asuint(input.DispatchThreadID);
	result.GroupIndex = asuint(input.GroupIndex);
	
	uint outAddress = input.GroupIndex * 10 * 4;
	
	Output.Store3(outAddress + 0, asuint(result.GroupID));
	Output.Store3(outAddress + 12, asuint(result.GroupThreadID));
	Output.Store3(outAddress + 24, asuint(result.DispatchThreadID));
	Output.Store(outAddress + 36, asuint(result.GroupIndex));
}


technique11 T0
{
	pass p0
	{
		SetVertexShader(NULL);
		SetPixelShader(NULL);

		SetComputeShader(CompileShader(cs_5_0, CS()));
	}
}