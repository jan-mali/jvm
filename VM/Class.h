#pragma once
#include "Method.h"
#include "../ClassFile/ConstantPool.h"

class VM;
class MethodArea;
class ClassFile;
class ClassLoader;

class Class {
public:
	static Class* from_class_file(VM* vm, ClassLoader* loader, ClassFile* class_file);
	void dump() const;

	Method* find_method(const char* name, const char* descriptor) const;

	[[nodiscard]] const char* name() const;
	[[nodiscard]] ConstantPool* constant_pool() const { return m_constant_pool; }
	[[nodiscard]] Class* super_class() const { return m_super_class; }
private:
	Class() = default;

	ClassLoader* m_initiating_loader = nullptr;
	ClassLoader* m_defining_loader = nullptr;

	ClassFile* m_class_file = nullptr;
	ConstantPool* m_constant_pool = nullptr;

	std::vector<Method*> m_methods {};

	Class* m_super_class = nullptr;

	// TODO: Super class
	// TODO: Fields
};