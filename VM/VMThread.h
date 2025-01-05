#pragma once
#include "CodeAddress.h"
#include "Frame.h"
#include "Method.h"

class Class;
class VM;

class VMThread {
	friend class VM;
public:
	static VMThread* create(VM* vm, Class* _class, Method* method);
private:
	VM* m_vm = nullptr;
	CodeAddress m_pc {};
	std::vector<Frame> m_frames{};
};