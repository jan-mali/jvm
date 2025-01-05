#include "Attributes.h"

#include <cassert>
#include <cstring>

#include "ConstantPool.h"

AttributesCreationResult Attributes::create(const uint8_t* data, const uint16_t attributes_count) {
	auto* attributes = new Attributes();

	const uint8_t* ptr = data;

	for (uint16_t i = 0; i < attributes_count; i++) {
		uint16_t attribute_name_index = (ptr[0] << 8) + ptr[1];
		ptr += sizeof(uint16_t);

		const uint32_t attribute_length = (ptr[0] << 24) + (ptr[1] << 16) + (ptr[2] << 8) + ptr[3];
		ptr += sizeof(uint32_t);

		RawAttribute attribute {};
		attribute.attribute_name_index = attribute_name_index;
		attribute.attribute_length = attribute_length;

		auto* attribute_info = new uint8_t[attribute_length];
		memcpy(attribute_info, ptr, attribute_length);

		attribute.info = attribute_info;

		ptr += attribute_length;

		attributes->m_attributes.push_back(attribute);
	}

	const size_t bytes = ptr - data;
	return {
		.attributes = attributes,
		.bytes = bytes
	};
}

Attributes::CodeAttribute Attributes::CodeAttribute::from_data(const uint8_t *data) {
	CodeAttribute attr {};

	const uint8_t* ptr = data;

	attr.max_stack = (ptr[0] << 8) + ptr[1];
	ptr += sizeof(uint16_t);

	attr.max_locals = (ptr[0] << 8) + ptr[1];
	ptr += sizeof(uint16_t);

	attr.code_length = (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3];
	ptr += sizeof(uint32_t);

	uint8_t* temp_code = new uint8_t[attr.code_length];
	memcpy(temp_code, ptr, attr.code_length);
	attr.code = temp_code;
	ptr += attr.code_length;

	attr.exception_table_length = (ptr[0] << 8) + ptr[1];
	ptr += sizeof(uint16_t);
	for (uint16_t i = 0; i < attr.exception_table_length; i++) {
		uint16_t start_pc = (ptr[0] << 8) + ptr[1];
		ptr += sizeof(uint16_t);

		uint16_t end_pc = (ptr[0] << 8) + ptr[1];
		ptr += sizeof(uint16_t);

		uint16_t handler_pc = (ptr[0] << 8) + ptr[1];
		ptr += sizeof(uint16_t);

		uint16_t catch_type = (ptr[0] << 8) + ptr[1];
		ptr += sizeof(uint16_t);

		attr.exception_table.push_back({
			.start_pc = start_pc,
			.end_pc = end_pc,
			.handler_pc = handler_pc,
			.catch_type = catch_type
		});
	}

	attr.attributes_count = (ptr[0] << 8) + ptr[1];
	ptr += sizeof(uint16_t);

	auto attribute_creation_result = create(ptr, attr.attributes_count);
	assert(attribute_creation_result.attributes);

	attr.attributes = attribute_creation_result.attributes;
	ptr += attribute_creation_result.bytes;

	return  attr;
}

Attributes::Attribute::~Attribute() {
	switch (attribute_type) {
		case PredefinedAttributeType::None:
			custom.~CustomAttribute();
			break;
		case PredefinedAttributeType::Code:
			code.~CodeAttribute();
			break;
		default:
			assert(false);
	}
}

void Attributes::for_each(ConstantPool* constant_pool, std::function<void(const char* , Attribute&)> cb) const {
	for (auto raw_attr: m_attributes) {
		ConstantPool::ConstantPoolEntry name_entry = constant_pool->get_jvm_index(raw_attr.attribute_name_index);
		assert(name_entry.tag == ConstantPool::Tag::Utf8);
		const char* name = name_entry.utf8.bytes;
		Attribute attribute {};
		attribute.attribute_type = PredefinedAttributeType::None;
		if (strcmp(name, "Code") == 0) {
			attribute.attribute_type = PredefinedAttributeType::Code;
			attribute.code = CodeAttribute::from_data(raw_attr.info);
		} else {
			attribute.attribute_type = PredefinedAttributeType::None;
			attribute.custom = {
				.length = raw_attr.attribute_length,
				.data = raw_attr.info
			};
		}
		cb(name, attribute);
	}
}
