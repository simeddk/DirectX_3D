#pragma once

class DebugLine
{
public:
	friend class Window;

private:
	static void Create();
	static void Delete();

public:
	static DebugLine* Get();

private:
	DebugLine();
	~DebugLine();

private:
	static DebugLine* instance;
};