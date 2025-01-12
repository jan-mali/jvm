#pragma once
#include <cassert>
#include <vector>

#include "../ClassFile/Attributes.h"
#include "Variable.h"

class Frame {
public:
	static Frame create(const Attributes::CodeAttribute& code_attribute);
	static Frame create_native();

	void push_operand(const Variable operand) {
		assert(m_operand_stack.size() < m_max_stack);
		m_operand_stack.push_back(operand);
	}
	Variable pop_operand() {
		assert(!m_operand_stack.empty());
		const Variable operand = m_operand_stack.back();
		m_operand_stack.pop_back();
		return operand;
	}
	[[nodiscard]] Variable peek_operand(const uint16_t index) const {
		assert(index < m_operand_stack.size());
		return m_operand_stack[m_operand_stack.size() - index - 1];
	}

	void store_local(const uint16_t index, const Variable variable) {
		assert(m_local_variables.size() == m_max_locals);
		assert(index < m_max_locals);
		m_local_variables[index] = variable;
	}
	[[nodiscard]] Variable read_local(const uint16_t index) const {
		assert(m_local_variables.size() == m_max_locals);
		assert(index < m_max_locals);
		return m_local_variables[index];
	}

private:
	Frame() = default;
	uint16_t m_max_locals = 0;
	uint16_t m_max_stack = 0;
	std::vector<Variable> m_local_variables{};
	std::vector<Variable> m_operand_stack{};
};
