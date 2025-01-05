#include "VMThread.h"

#include "Instructions.h"

VMThread* VMThread::create(VM* vm, Class* _class, Method* method) {
	auto* thread = new VMThread();
	thread->m_vm = vm;
	thread->m_pc = { _class, method, 0 };
	thread->m_frames.push_back(Frame::create(method->code_attribute()));
	return thread;
}

void VMThread::schedule() {
	if (is_terminating()) {
		// TODO: Clean up?
		return;
	}
	Attributes::CodeAttribute code_attr = m_pc.method->code_attribute();
	assert(m_pc.instruction < code_attr.code_length);
	uint8_t opcode = code_attr.code[m_pc.instruction];
	uint16_t bytes = Instructions::execute(opcode, m_vm, this, current_frame(), m_pc._class, m_pc.method);
	// FIXME: This won't work if an instruction changes the PC
	m_pc.instruction += bytes;
}
