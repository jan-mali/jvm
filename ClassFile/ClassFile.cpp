//
// Created by gameefan on 04.01.25.
//

#include "ClassFile.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "AccessFlags.h"

// https://docs.oracle.com/javase/specs/jvms/se23/html/jvms-4.html#jvms-4.1
ClassFile* ClassFile::create(const uint8_t* data) {
	auto* class_file = new ClassFile();

	const uint8_t* ptr = data;
	const uint32_t magic = (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3];
	ptr += sizeof(uint32_t);

	if (magic != 0xCAFEBABE) {
		printf("ClassFile::create: invalid magic number 0x%x\n", magic);
		return nullptr;
	}

	const uint16_t minor_version = (ptr[0] << 8) | ptr[1];
	ptr += sizeof(uint16_t);
	class_file->m_minor_version = minor_version;

	const uint16_t major_version = (ptr[0] << 8) | ptr[1];
	ptr += sizeof(uint16_t);
	class_file->m_minor_version = major_version;

	if (major_version > 67) {
		printf("ClassFile::create: unsupported major version %d\n", major_version);
		return nullptr;
	}

	if (minor_version != 0) {
		printf("ClassFile::create: unsupported minor version %d\n", minor_version);
		printf("\tPlease don't use preview features\n");
		return nullptr;
	}

	const uint16_t constant_pool_count = ((ptr[0] << 8) | ptr[1]) - 1;
	ptr += sizeof(uint16_t);
	class_file->m_constant_pool_count = constant_pool_count;

	ConstantPoolCreationResult constant_pool_creation_result = ConstantPool::create(ptr, constant_pool_count);
	if (!constant_pool_creation_result.pool) {
		printf("ClassFile::create: constant pool creation failed\n");
		return nullptr;
	}

	ConstantPool* constant_pool = constant_pool_creation_result.pool;
	ptr += constant_pool_creation_result.bytes;

	class_file->m_constant_pool = constant_pool;

	// TODO: Remove this once we can dump a Class
	printf("ClassFile::create: constant pool creation successful\n");
	printf("Loaded following entries:\n");
	constant_pool->dump(1);

	uint16_t raw_flags = (ptr[0] << 8) | ptr[1];
	ptr += sizeof(uint16_t);
	const auto access_flags = AccessFlags(raw_flags);

	// TODO: Remove this once we can dump a Class
	printf("ClassFile::create: access_flags: ");
	access_flags.dump();
	printf("\n");

	class_file->m_access_flags = access_flags;

	if (access_flags.is_module()) {
		// TODO: Special treatment & checks
		printf("ClassFile::create: ACC_MODULE is set, this is currently unsupported\n");
		return nullptr;
	}

	const uint16_t this_class = (ptr[0] << 8) | ptr[1];
	ptr += sizeof(uint16_t);

	const uint16_t super_class = (ptr[0] << 8) | ptr[1];
	ptr += sizeof(uint16_t);

	class_file->m_this_class = this_class;
	class_file->m_super_class = super_class;

	uint16_t interfaces_count = (ptr[0] << 8) | ptr[1];
	ptr += sizeof(uint16_t);
	class_file->m_interfaces_count = interfaces_count;

	auto* interfaces = static_cast<uint16_t*>(calloc(interfaces_count, sizeof(uint16_t)));
	if (!interfaces) {
		printf("ClassFile::create: calloc failed\n");
		free(interfaces);
		return nullptr;
	}

	// TODO: Remove this once we begin loading interfaces
	for (uint16_t i = 0; i < interfaces_count; i++) {
		const uint16_t interface = (ptr[0] << 8) | ptr[1];
		ptr += sizeof(uint16_t);
		interfaces[i] = interface;
		printf("ClassFile::create: -> interface @ %d\n", interface);
	}

	class_file->m_interfaces = interfaces;

	uint16_t fields_count = (ptr[0] << 8) | ptr[1];
	ptr += sizeof(uint16_t);
	class_file->m_fields_count = fields_count;

	FieldsCreationResult fields_creation_result = Fields::create(ptr, fields_count);
	if (!fields_creation_result.fields) {
		printf("ClassFile::create: fields creation failed\n");
		free(interfaces);
		return nullptr;
	}

	Fields* fields = fields_creation_result.fields;
	ptr += fields_creation_result.bytes;

	class_file->m_fields = fields;

	uint16_t methods_count = (ptr[0] << 8) | ptr[1];
	ptr += sizeof(uint16_t);
	class_file->m_methods_count = methods_count;

	MethodsCreationResult methods_creation_result = Methods::create(ptr, methods_count);
	if (!methods_creation_result.methods) {
		printf("ClassFile::create: methods creation failed\n");
		free(interfaces);
		return nullptr;
	}

	Methods* methods = methods_creation_result.methods;
	ptr += methods_creation_result.bytes;

	class_file->m_methods = methods;

	uint16_t attributes_count = (ptr[0] << 8) | ptr[1];
	ptr += sizeof(uint16_t);

	AttributesCreationResult attributes_creation_result = Attributes::create(ptr, attributes_count);
	if (!attributes_creation_result.attributes) {
		printf("ClassFile::create: attributes creation failed\n");
		free(interfaces);
		return nullptr;
	}
	Attributes* attributes = attributes_creation_result.attributes;
	ptr += attributes_creation_result.bytes;
	class_file->m_attributes = attributes;

	// TODO: Class file verification & type checking

	printf("ClassFile has been loaded successfully\n");

	return class_file;
}

ClassFile* ClassFile::create_from_path(const char* path) {
	uint8_t* data = nullptr;

	auto* file = fopen(path, "rb");
	if (!file) {
		perror("Failed to open class file");
		return nullptr;
	}

	fseek(file, 0, SEEK_END);
	const size_t length = ftell(file);
	fseek(file, 0, SEEK_SET);

	data = static_cast<uint8_t*>(malloc(length + 1));

	if (!data) {
		perror("Failed to allocate memory for class file");
		return nullptr;
	}

	uint8_t* temp = data;
	while (fread(temp, 1, 1, file) > 0) {
		temp++;
		fflush(file);
	}
	assert(feof(file));
	assert(!ferror(file));

	data[length] = 0;

	printf("%s is loaded at %p\n", path, data);
	printf("Read %llu bytes from %s\n", length, path);

	ClassFile* class_file = create(data);

	free(data);

	return class_file;
}
