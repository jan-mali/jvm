#pragma once
#include "MethodArea.h"
#include "../Loader/BootstrapClassLoader.h"

class Class;

class VM {
public:
	void start(const char* class_name);
	void add_class(Class* _class);
private:
	BootstrapClassLoader m_bootstrap_class_loader;
	MethodArea m_method_area;
};
