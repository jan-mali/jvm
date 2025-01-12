#include "Class.h"

#include <cassert>
#include <cstdio>
#include <cstring>

#include "../ClassFile/ClassFile.h"
#include "VM.h"

// https://docs.oracle.com/javase/specs/jvms/se23/html/jvms-5.html#jvms-5.3.5
Class* Class::from_class_file(VM* vm, ClassLoader* loader, ClassFile* class_file) {
	auto* _class = new Class();
	_class->m_initiating_loader = _class->m_defining_loader = loader;

	_class->m_class_file = class_file;
	_class->m_constant_pool = class_file->constant_pool();

	class_file->methods()->for_each([_class](Methods::MethodInfo mi) {
		Method* method = Method::from_method_info(_class->m_constant_pool, mi);
		_class->m_methods.push_back(method);
	});

	if (strcmp(_class->name(), "java/lang/Object") != 0) {
		ConstantPool::ConstantPoolEntry super_class_entry = class_file->constant_pool()->get_jvm_index(class_file->super_class());
		assert(super_class_entry.tag == ConstantPool::Tag::Class);
		uint16_t super_class_name_index = super_class_entry._class.name_index;

		ConstantPool::ConstantPoolEntry super_class_name_entry = class_file->constant_pool()->get_jvm_index(super_class_name_index);
		assert(super_class_name_entry.tag == ConstantPool::Tag::Utf8);
		const char* super_class_name = super_class_name_entry.utf8.bytes;

		// FIXME: This should really be done by the MethodArea, not the VM
		Class* super_class = vm->get_class(super_class_name);
		assert(super_class);
		_class->m_super_class = super_class;
	}

	class_file->attributes()->for_each(_class->m_constant_pool, [](const char* attr_name, Attributes::Attribute& attr) {
		switch (attr.attribute_type) {
		case Attributes::PredefinedAttributeType::SourceFile:
		case Attributes::PredefinedAttributeType::InnerClasses:
		case Attributes::PredefinedAttributeType::EnclosingMethod:
		case Attributes::PredefinedAttributeType::SourceDebugExtension:
		case Attributes::PredefinedAttributeType::BootstrapMethods:
		case Attributes::PredefinedAttributeType::Module:
		case Attributes::PredefinedAttributeType::ModulePackages:
		case Attributes::PredefinedAttributeType::ModuleMainClass:
		case Attributes::PredefinedAttributeType::NestHost:
		case Attributes::PredefinedAttributeType::NestMembers:
		case Attributes::PredefinedAttributeType::Record:
		case Attributes::PredefinedAttributeType::PermittedSubclasses:
			// TODO: Implement
			printf("\tTODO: Implement attribute %s\n", attr_name);
			break;
		default:
			// Ignore custom attributes
			printf("\tSkipping custom attribute %s\n", attr_name);
			break;
		}
	});

	return _class;
}

void Class::dump() const {
	printf("Class dump: %s\n", name());
}

Method* Class::find_method(const char* name, const char* descriptor) const {
	for (auto method : m_methods) {
		if (strcmp(method->name(), name) != 0)
			continue;
		if (strcmp(method->descriptor(), descriptor) != 0)
			continue;
		return method;
	}
	return nullptr;
}

const char* Class::name() const {
	auto class_entry = m_constant_pool->get_jvm_index(m_class_file->this_class());
	assert(class_entry.tag == ConstantPool::Tag::Class);

	auto name_entry = m_constant_pool->get_jvm_index(class_entry._class.name_index);
	assert(name_entry.tag == ConstantPool::Tag::Utf8);

	return name_entry.utf8.bytes;
}
