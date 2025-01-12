#include "VMThread.h"

#include "Instructions.h"
#include "VM.h"

VMThread* VMThread::create(VM* vm, Class* _class, Method* method) {
	auto* thread = new VMThread();
	thread->m_vm = vm;
	thread->m_pc_stack.push_back({_class, method, 0});
	thread->m_frames.push_back(Frame::create(method->code_attribute()));
	return thread;
}

void VMThread::schedule() {
	if (is_terminating()) {
		// TODO: Clean up?
		return;
	}

	// This ensures that invoking a new method doesn't mess up our PC
	if (m_is_next_pc_ready) {
		m_is_next_pc_ready = false;
		m_pc_stack.push_back(m_next_pc);
	}

	CodeAddress current_pc = pc();

	Method* current_method = current_pc.method;
	if (current_method->access_flags().is_native()) {
		NativeClass* native_class = m_vm->native_class_registry()->get_native_class(current_pc._class->name());
		assert(native_class);
		bool ok = native_class->execute_function(current_method->name(), current_method->descriptor(), m_vm, this, current_frame(), current_pc._class, current_method);

		if (!ok) {
			printf("VMThread::schedule: NativeClass::execute_function failed\n");
			assert(ok);
		}

		// NOTE: The function is expected to call thread->handle_return() to return control to the invoker

		return;
	}

	const Attributes::CodeAttribute code_attr = current_pc.method->code_attribute();
	assert(current_pc.instruction < code_attr.code_length);
	const uint8_t opcode = code_attr.code[current_pc.instruction];
	const uint16_t bytes = Instructions::execute(opcode, m_vm, this, current_frame(), current_pc._class, current_pc.method);

	if (bytes > 0) {
		// When bytes == 0 it means that we have executed a return instruction and the PC should not be touched because
		// the invoker's Frame & PC have already been reinstated
		current_pc.instruction += bytes;
		set_current_pc(current_pc);
	}
}

void VMThread::handle_return() {
	m_frames.pop_back();
	if (m_frames.empty()) {
		terminate();
		return;
	}
	m_pc_stack.pop_back();
}

void VMThread::prepare_invocation(const CodeAddress& next_pc, const Frame& frame) {
	m_frames.push_back(frame);
	set_next_pc(next_pc);
}
