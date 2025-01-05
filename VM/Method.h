#pragma once

#include "../ClassFile/Methods.h"

class ConstantPool;

class Method {
public:
	static Method* from_method_info(ConstantPool* constant_pool, Methods::MethodInfo method_info);

	[[nodiscard]] Attributes::CodeAttribute code_attribute() const { return m_code_attribute; }
	[[nodiscard]] Attributes::LineNumberTable line_number_table() const { return m_line_number_table_attribute; }

	[[nodiscard]] const char* name() const { return m_name; }
	[[nodiscard]] const char* descriptor() const { return m_descriptor; }
private:
	Method() = default;

	AccessFlags m_access_flags { 0 };
	const char* m_name = nullptr;
	const char* m_descriptor = nullptr;

	Attributes::CodeAttribute m_code_attribute {};
	Attributes::LineNumberTable m_line_number_table_attribute {};
};
