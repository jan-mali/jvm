#include "Class.h"

#include <cassert>
#include <cstdio>

#include "../ClassFile/ClassFile.h"

// https://docs.oracle.com/javase/specs/jvms/se23/html/jvms-5.html#jvms-5.3.5
Class* Class::from_class_file(ClassLoader* loader, ClassFile* class_file) {
	auto* _class = new Class();
	_class->m_initiating_loader = _class->m_defining_loader = loader;

	_class->m_class_file = class_file;
	_class->m_constant_pool = class_file->constant_pool();

	class_file->methods()->for_each([_class](Methods::MethodInfo mi) {
		const Method method = Method::from_method_info(_class->m_constant_pool, mi);
		_class->m_methods.push_back(method);
	});

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

const char* Class::name() const {
	auto class_entry = m_constant_pool->get_jvm_index(m_class_file->this_class());
	assert(class_entry.tag == ConstantPool::Tag::Class);

	auto name_entry = m_constant_pool->get_jvm_index(class_entry._class.name_index);
	assert(name_entry.tag == ConstantPool::Tag::Utf8);

	return name_entry.utf8.bytes;
}
