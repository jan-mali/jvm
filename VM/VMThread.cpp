#include "VMThread.h"

#include "Instructions.h"

VMThread* VMThread::create(VM* vm, Class* _class, Method* method) {
	auto* thread = new VMThread();
	thread->m_vm = vm;
	thread->m_pc_stack.push_back({ _class, method, 0 });
	thread->m_frames.push_back(Frame::create(method->code_attribute()));
	return thread;
}

void VMThread::schedule() {
	if (is_terminating()) {
		// TODO: Clean up?
		return;
	}
	CodeAddress current_pc = pc();
	Attributes::CodeAttribute code_attr = current_pc.method->code_attribute();
	assert(current_pc.instruction < code_attr.code_length);
	const uint8_t opcode = code_attr.code[current_pc.instruction];
	const uint16_t bytes = Instructions::execute(opcode, m_vm, this, current_frame(), current_pc._class, current_pc.method);

	// FIXME: This won't work if an instruction changes the PC
	current_pc.instruction += bytes;
	set_current_pc(current_pc);
}

void VMThread::handle_return() {
	m_frames.pop_back();
	if (m_frames.empty()) {
		terminate();
		return;
	}
	m_pc_stack.pop_back();
}
