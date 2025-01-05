#pragma once

#include "../ClassFile/Methods.h"

class ConstantPool;

class Method {
public:
	static Method from_method_info(ConstantPool* constant_pool, Methods::MethodInfo method_info);
private:
	Method() = default;

	AccessFlags m_access_flags { 0 };
	const char* m_name = nullptr;
	const char* m_descriptor = nullptr;

	Attributes::CodeAttribute m_code_attribute {};
};
