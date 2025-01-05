#pragma once
#include <vector>

#include "ClassLoader.h"

class VM;
class Class;

// https://docs.oracle.com/javase/specs/jvms/se23/html/jvms-5.html#jvms-5.3.1
class BootstrapClassLoader final : public ClassLoader {
public:
	void load_class(VM *vm, const char *class_name) override;
private:
};