#include "Methods.h"

MethodsCreationResult Methods::create(const uint8_t* data, uint16_t Methods_count) {
	auto* methods = new Methods();

	const uint8_t* ptr = data;

	for (uint16_t i = 0; i < Methods_count; i++) {
		MethodInfo mi {};

		const uint16_t raw_flags = (ptr[0] << 8) | ptr[1];
		ptr += sizeof(uint16_t);
		const auto access_flags = AccessFlags(raw_flags);
		mi.access_flags = access_flags;

		uint16_t name_index = (ptr[0] << 8) | ptr[1];
		ptr += sizeof(uint16_t);

		uint16_t description_index = (ptr[0] << 8) | ptr[1];
		ptr += sizeof(uint16_t);

		uint16_t attributes_count = (ptr[0] << 8) | ptr[1];
		ptr += sizeof(uint16_t);

		mi.name_index = name_index;
		mi.descriptor_index = description_index;
		mi.attributes_count = attributes_count;

		AttributesCreationResult attributes_creation_result = Attributes::create(ptr, attributes_count);
		if (!attributes_creation_result.attributes) {
			printf("Failed to create attributes for method %d\n", i);
			ptr += attributes_creation_result.bytes;
			continue;
		}
		mi.attributes = attributes_creation_result.attributes;
		ptr += attributes_creation_result.bytes;

		methods->m_methods.push_back(mi);
	}

	const size_t bytes = ptr - data;
	return {
		.methods = methods,
		.bytes = bytes
	};
}
