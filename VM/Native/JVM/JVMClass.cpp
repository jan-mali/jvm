#include "JVMClass.h"

#include <cstdio>
#include <cstring>

#include "../../Frame.h"
#include "../../VMThread.h"

bool JVMClass::execute_function(const char* name, const char* descriptor, VM* vm, VMThread* thread, Frame& frame, Class *_class, Method *method) {
	if (strcmp(name, "testRuntime") == 0 && strcmp(descriptor, "(I)V") == 0) {
		func$testRuntime(vm, thread, frame, _class, method);
		return true;
	}
	return false;
}

void JVMClass::func$testRuntime(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	Variable value = frame.read_local(0);
	printf("testRuntime: %d\n", value.value);
	thread->handle_return();
}
