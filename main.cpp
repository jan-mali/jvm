#include <cstring>
#include <iostream>

#include "ClassFile/ClassFile.h"
#include "VM/VM.h"

// Spec link: https://docs.oracle.com/javase/specs/jvms/se23/html/index.html
int main(int argc, char** argv) {
	if (argc < 2 || strcmp(argv[1], "--help") == 0) {
		printf("Usage: %s <class name>\n", argv[0]);
		printf("       %s --help\n", argv[0]);
		printf("\n");
		printf("Options:\n");
		printf("\t--help Show this help and exit\n");
		return 1;
	}

	const char* class_name = argv[1];

	const auto vm = new VM();
	vm->start(class_name);

	return 0;
}
