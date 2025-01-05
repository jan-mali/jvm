#pragma once
#include <cassert>

#include "CodeAddress.h"
#include "Frame.h"
#include "Method.h"

class Class;
class VM;

class VMThread {
	friend class VM;
public:
	static VMThread* create(VM* vm, Class* _class, Method* method);
	void schedule();

	void terminate() { m_is_terminating = true; }
	[[nodiscard]] bool is_terminating() const { return m_is_terminating; }

	[[nodiscard]] CodeAddress pc() const {
		assert(!m_pc_stack.empty());
		return m_pc_stack.back();
	}
	void set_current_pc(const CodeAddress& pc) {
		assert(!m_pc_stack.empty());
		m_pc_stack.pop_back();
		m_pc_stack.push_back(pc);
	}

	void handle_return();

private:
	VM* m_vm = nullptr;
	std::vector<CodeAddress> m_pc_stack{};
	std::vector<Frame> m_frames{};

	bool m_is_terminating = false;

	Frame& current_frame() {
		assert(!m_frames.empty());
		return m_frames.back();
	}
};