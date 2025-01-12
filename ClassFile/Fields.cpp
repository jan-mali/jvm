#include "Fields.h"

FieldsCreationResult Fields::create(const uint8_t* data, uint16_t fields_count) {
	auto* fields = new Fields();

	const uint8_t* ptr = data;

	for (uint16_t i = 0; i < fields_count; i++) {
		FieldInfo fi{};

		const uint16_t raw_flags = (ptr[0] << 8) | ptr[1];
		ptr += sizeof(uint16_t);
		const auto access_flags = AccessFlags(raw_flags);
		fi.access_flags = access_flags;

		uint16_t name_index = (ptr[0] << 8) | ptr[1];
		ptr += sizeof(uint16_t);

		uint16_t description_index = (ptr[0] << 8) | ptr[1];
		ptr += sizeof(uint16_t);

		uint16_t attributes_count = (ptr[0] << 8) | ptr[1];
		ptr += sizeof(uint16_t);

		fi.name_index = name_index;
		fi.descriptor_index = description_index;
		fi.attributes_count = attributes_count;

		AttributesCreationResult attributes_creation_result = Attributes::create(ptr, attributes_count);
		if (!attributes_creation_result.attributes) {
			printf("Failed to create attributes for field %d\n", i);
			ptr += attributes_creation_result.bytes;
			continue;
		}
		fi.attributes = attributes_creation_result.attributes;
		ptr += attributes_creation_result.bytes;

		fields->m_fields.push_back(fi);
	}

	const size_t bytes = ptr - data;
	return {
			.fields = fields,
			.bytes = bytes};
}
