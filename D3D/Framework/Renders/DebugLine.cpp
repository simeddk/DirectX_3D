#include "Framework.h"
#include "DebugLine.h"

DebugLine* DebugLine::instance = nullptr;

void DebugLine::Create()
{
	assert(instance == nullptr);

	instance = new DebugLine();
}

void DebugLine::Delete()
{
	SafeDelete(instance);
}

DebugLine* DebugLine::Get()
{
	assert(instance != nullptr);

	return instance;
}

DebugLine::DebugLine()
{
	//Todo... 
}

DebugLine::~DebugLine()
{
}
