#include "VM.h"

void VM::start(const char* class_name) {
	m_bootstrap_class_loader.load_class(this, class_name);

	m_method_area.dump();

	// TODO: Invoke `public static method void main(String[])`
}

void VM::add_class(Class* _class) {
	m_method_area.add_class(_class);
}
