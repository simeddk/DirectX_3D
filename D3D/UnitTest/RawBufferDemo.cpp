#include "stdafx.h"
#include "RawBufferDemo.h"

void RawBufferDemo::Initialize()
{
	Shader* shader = new Shader(L"16_ByteAddress.fxo");

	UINT count = 10 * 8 * 3 * 2;

	struct Output
	{
		UINT GroupID[3];
		UINT GroupThreadID[3];
		UINT DispatchThreadID[3];
		UINT GroupIndex;
		float RetVal;
	};

	float* inputDatas = new float[count];
	for (UINT i = 0; i < count; i++)
		inputDatas[i] = (float)i;

	RawBuffer* rawBuffer = new RawBuffer(inputDatas, sizeof(float) * count, sizeof(Output) * count);

	shader->AsSRV("Input")->SetResource(rawBuffer->SRV());
	shader->AsUAV("Output")->SetUnorderedAccessView(rawBuffer->UAV());
	shader->Dispatch(0, 0, 2, 1, 1);

	Output* output = new Output[count];
	rawBuffer->CopyFromOutput(output);

	FILE* fileBuffer;
	fopen_s(&fileBuffer, "../ThreadID.csv", "w");
	{

		for (UINT i = 0; i < count; i++)
		{
			Output temp = output[i];

			fprintf
			(
				fileBuffer,
				"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f\n",
				temp.GroupID[0], temp.GroupID[1], temp.GroupID[2],
				temp.GroupThreadID[0], temp.GroupThreadID[1], temp.GroupThreadID[2],
				temp.DispatchThreadID[0], temp.DispatchThreadID[1], temp.DispatchThreadID[2],
				temp.GroupIndex,
				temp.RetVal
			);
		}
	}
	fclose(fileBuffer);
}

void RawBufferDemo::Destroy()
{

}
