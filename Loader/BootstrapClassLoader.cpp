#include "BootstrapClassLoader.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "../ClassFile/ClassFile.h"
#include "../VM/Class.h"
#include "../VM/VM.h"

void BootstrapClassLoader::load_class(VM* vm, const char* class_name) {

	// TODO: Properly look for the class

	auto class_path = static_cast<char *>(malloc(strlen(class_name) + 9));
	strcpy(class_path, "./");
	strcat(class_path, class_name);
	strcat(class_path, ".class");
	printf("Loading class %s from path %s\n", class_name, class_path);

	// TODO: Check if the class was loaded before

	ClassFile* class_file = ClassFile::create_from_path(class_path);
	if (!class_file) {
		// TODO: Throw exception
		printf("Failed to load class %s\n", class_name);
		abort();
	}

	Class* _class = Class::from_class_file(this, class_file);
	if (!_class) {
		// TODO: Throw exception
		printf("Failed to load class %s\n", class_name);
		abort();
	}

	m_initiating_loader_for_classes.push_back(class_name);
	m_defining_loader_for_classes.push_back(class_name);

	vm->add_class(_class);

	free(class_path);
}
