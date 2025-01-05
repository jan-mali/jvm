#include "VM.h"

void VM::start(const char* class_name) {
	Class* _class = m_bootstrap_class_loader.load_class(this, class_name);

	m_method_area.dump();

	invoke_main(_class);
}

void VM::add_class(Class* _class) {
	m_method_area.add_class(_class);
}

void VM::invoke_main(Class* _class) {
	Method* main = _class->find_method("main", "([Ljava/lang/String;)V");
	if (!main) {
		printf("VM::invoke_main: method 'main' not found\n");
		return;
	}
	VMThread* main_thread = VMThread::create(this, _class, main);
	m_threads.push_back(main_thread);
	// TODO: Start a proper multi-threaded scheduler
	schedule_single(main_thread);
}

void VM::schedule_single(VMThread* thread) {
	printf("Starting execution of a single thread\n");
	// TODO: Actually run the program
}
