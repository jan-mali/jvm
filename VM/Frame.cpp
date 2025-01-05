#include "Frame.h"

Frame Frame::create(const Attributes::CodeAttribute& code_attribute) {
	Frame frame;
	frame.m_max_stack = code_attribute.max_stack;
	frame.m_max_locals = code_attribute.max_locals;
	frame.m_local_variables = std::vector<Variable>(code_attribute.max_locals, Variable());
	return frame;
}
