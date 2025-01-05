#pragma once
#include <vector>

#include "Variable.h"
#include "../ClassFile/Attributes.h"

class Frame {
public:
	static Frame create(const Attributes::CodeAttribute& code_attribute);
private:
	Frame() = default;
	uint16_t m_max_locals = 0;
	uint16_t m_max_stack = 0;
	std::vector<Variable> m_local_variables {};
	std::vector<Variable> m_operand_stack {};
};
