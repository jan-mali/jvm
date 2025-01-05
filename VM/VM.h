#pragma once
#include "MethodArea.h"
#include "../Loader/BootstrapClassLoader.h"
#include "VMThread.h"

class Class;

class VM {
public:

	void start(const char* class_name);
	void add_class(Class* _class);

	Class* get_class(const char* class_name);

private:
	BootstrapClassLoader m_bootstrap_class_loader;
	MethodArea m_method_area;
	std::vector<VMThread*> m_threads;
	void invoke_main(Class* _class);
	void schedule_single(VMThread* thread);
};
