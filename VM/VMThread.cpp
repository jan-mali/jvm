#include "VMThread.h"

VMThread* VMThread::create(VM* vm, Class* _class, Method* method) {
	auto* thread = new VMThread();
	thread->m_vm = vm;
	thread->m_pc = { _class, method, 0 };
	thread->m_frames.push_back(Frame::create(method->code_attribute()));
	return thread;
}
