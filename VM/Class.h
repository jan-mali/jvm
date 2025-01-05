#pragma once
#include "Method.h"
#include "../ClassFile/ConstantPool.h"

class MethodArea;
class ClassFile;
class ClassLoader;

class Class {
public:
	static Class* from_class_file(ClassLoader* loader, ClassFile* class_file);
	void dump() const;

	Method* find_method(const char* name, const char* descriptor) const;

	[[nodiscard]] const char* name() const;
	[[nodiscard]] ConstantPool* constant_pool() const { return m_constant_pool; }
private:
	Class() = default;

	ClassLoader* m_initiating_loader = nullptr;
	ClassLoader* m_defining_loader = nullptr;

	ClassFile* m_class_file = nullptr;
	ConstantPool* m_constant_pool = nullptr;

	std::vector<Method*> m_methods {};

	// TODO: Super class
	// TODO: Fields
};