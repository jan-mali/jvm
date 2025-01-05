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

private:
	VM* m_vm = nullptr;
	CodeAddress m_pc {};
	std::vector<Frame> m_frames{};

	bool m_is_terminating = false;

	Frame& current_frame() {
		assert(!m_frames.empty());
		return m_frames.back();
	}
};