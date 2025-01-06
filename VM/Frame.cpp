#include "Frame.h"

Frame Frame::create(const Attributes::CodeAttribute& code_attribute) {
	Frame frame;
	frame.m_max_stack = code_attribute.max_stack;
	frame.m_max_locals = code_attribute.max_locals;
	frame.m_local_variables = std::vector<Variable>(code_attribute.max_locals, Variable());
	return frame;
}

Frame Frame::create_native() {
	Frame frame;
	// The only thing that we care about here is the local variables, and we probably won't need any more than 256
	frame.m_max_stack = 0;
	frame.m_max_locals = 256;
	frame.m_local_variables = std::vector<Variable>(256, Variable());
	return frame;
}
