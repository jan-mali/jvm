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

	method_info.attributes->for_each(constant_pool, [&method](const char* attr_name, Attributes::Attribute& attr) {
		switch (attr.attribute_type) {
			case Attributes::PredefinedAttributeType::Code:
				method.m_code_attribute = attr.code;
				// TODO: LineNumberTable
				break;
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
				break;
		}
	});

	return method;
}
