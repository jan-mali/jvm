#include "Method.h"

#include <cassert>

#include "../ClassFile/ConstantPool.h"

Method Method::from_method_info(ConstantPool* constant_pool, Methods::MethodInfo method_info) {
	Method method {};

	method.m_access_flags = method_info.access_flags;

	ConstantPool::ConstantPoolEntry name_entry = constant_pool->get_jvm_index(method_info.name_index);
	assert(name_entry.tag == ConstantPool::Tag::Utf8);
	method.m_name = name_entry.utf8.bytes;

	ConstantPool::ConstantPoolEntry descriptor_entry = constant_pool->get_jvm_index(method_info.descriptor_index);
	assert(descriptor_entry.tag == ConstantPool::Tag::Utf8);
	method.m_descriptor = descriptor_entry.utf8.bytes;

	method_info.attributes->for_each(constant_pool, [&method, constant_pool](const char* attr_name, Attributes::Attribute& attr) {
		switch (attr.attribute_type) {
			case Attributes::PredefinedAttributeType::Code: {
				Attributes::CodeAttribute code = attr.code;

				method.m_code_attribute = code;

				code.attributes->for_each(constant_pool, [&method](const char* code_attr_name, Attributes::Attribute& code_attr) {
					// We only want the LineNumberTable for now
					if (code_attr.attribute_type == Attributes::PredefinedAttributeType::LineNumberTable) {
						method.m_line_number_table_attribute = code_attr.line_number_table;
						return;
					}
					printf("Skipping Code attr's attribute: %s\n", code_attr_name);
				});

				break;
			}
			case Attributes::PredefinedAttributeType::Exceptions:
			case Attributes::PredefinedAttributeType::RuntimeVisibleParameterAnnotations:
			case Attributes::PredefinedAttributeType::RuntimeInvisibleParameterAnnotations:
			case Attributes::PredefinedAttributeType::AnnotationDefault:
			case Attributes::PredefinedAttributeType::MethodParameters:
				// TODO: Implement
				printf("\tTODO: Implement attribute %s\n", attr_name);
				break;
			default:
				// We don't care about any custom attributes
				printf("\tSkipping custom attribute %s\n", attr_name);
				break;
		}
	});

	return method;
}
