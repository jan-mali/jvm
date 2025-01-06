#pragma once
#include "MethodArea.h"
#include "../Loader/BootstrapClassLoader.h"
#include "VMThread.h"
#include "Native/NativeClassRegistry.h"

class Class;

class VM {
public:

	void register_native_classes();
	void start(const char* class_name);
	void add_class(Class* _class);

	Class* get_class(const char* class_name);
	NativeClassRegistry* native_class_registry() const { return m_native_class_registry; };

private:
	BootstrapClassLoader m_bootstrap_class_loader;
	MethodArea m_method_area;
	std::vector<VMThread*> m_threads;
	NativeClassRegistry* m_native_class_registry = nullptr;

	void invoke_main(Class* _class);
	void schedule_single(VMThread* thread);
};
