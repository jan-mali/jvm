#include "Attributes.h"

#include <cstring>

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
