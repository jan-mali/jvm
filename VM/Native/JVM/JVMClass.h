#pragma once
#include "../NativeClass.h"

class JVMClass : public NativeClass {
public:
	JVMClass() {
		set_name("jvm/JVM");
	}
	bool execute_function(const char* name, const char* descriptor, VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) override;

private:
	void func$testRuntime(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method);
	void func$testRuntimeLong(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method);
};
