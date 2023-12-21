ByteAddressBuffer Input;
RWByteAddressBuffer Output;

struct ComputeInput
{
	uint3 GroupID : SV_GroupID;						//Dispatch���� ���� ���� ���� ���� ������ID(Vec3)
	uint3 GroupThreadID : SV_GroupThreadID;			//�׷� �� ���� ������ID(Vec3)
	uint3 DispatchThreadID : SV_DispatchThreadID;	//��ü ������ �۷ι� ������ID(Vec3)
	uint GroupIndex : SV_GroupIndex;				//�׷� �� ���� 1����ȭ�� �ε���
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
	
	uint inAddress = (input.GroupID.x * 240 + input.GroupIndex) * 4;;
	float value = asfloat(Input.Load(inAddress)) * 100.f;
	
	uint outAddress = (input.GroupID.x * 240 + input.GroupIndex) * 11 * 4;
	
	Output.Store3(outAddress + 0, asuint(result.GroupID));
	Output.Store3(outAddress + 12, asuint(result.GroupThreadID));
	Output.Store3(outAddress + 24, asuint(result.DispatchThreadID));
	Output.Store(outAddress + 36, asuint(result.GroupIndex));
	Output.Store(outAddress + 40, asuint(value));

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