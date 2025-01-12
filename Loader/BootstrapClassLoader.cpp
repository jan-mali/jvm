#include "BootstrapClassLoader.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "../ClassFile/ClassFile.h"
#include "../Utils/HashTools.h"
#include "../VM/Class.h"
#include "../VM/VM.h"

Class* BootstrapClassLoader::load_class(VM* vm, const char* class_name) {
	// Check if the class was loaded before
	uint64_t hash = HashTools::fnv1a_hash(reinterpret_cast<const uint8_t*>(class_name), strlen(class_name));

	if (m_loaded_classes.contains(hash)) {
		printf("Class %s already loaded\n", class_name);
		return m_loaded_classes[hash];
	}

	// TODO: Properly look for the class

	auto class_path = static_cast<char*>(malloc(strlen(class_name) + 15));
	strcpy(class_path, "Runtime/");
	strcat(class_path, class_name);
	strcat(class_path, ".class");
	printf("Loading class %s from path %s\n", class_name, class_path);

	ClassFile* class_file = ClassFile::create_from_path(class_path);
	if (!class_file) {
		printf("Failed to load class %s from Runtime, checking CWD\n", class_name);
		strcpy(class_path, "./");
		strcat(class_path, class_name);
		strcat(class_path, ".class");
		class_file = ClassFile::create_from_path(class_path);
	}

	if (!class_file) {
		printf("Failed to load class %s from CWD, aborting\n", class_name);
		return nullptr;
	}

	Class* _class = Class::from_class_file(vm, this, class_file);
	if (!_class) {
		// TODO: Throw exception
		printf("Failed to load class %s\n", class_name);
		abort();
	}

	m_initiating_loader_for_classes.push_back(hash);

	// TODO: Check for circular dependencies

	m_defining_loader_for_classes.push_back(hash);

	vm->add_class(_class);

	m_loaded_classes[hash] = _class;

	free(class_path);

	return _class;
}
