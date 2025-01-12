#pragma once
#include <cstdint>
#include <vector>

#include "AccessFlags.h"
#include "Attributes.h"

class Fields;

struct FieldsCreationResult {
	Fields* fields;
	size_t bytes;
};

class Fields {
public:
	static FieldsCreationResult create(const uint8_t* data, uint16_t fields_count);

	struct FieldInfo {
		AccessFlags access_flags{0};
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t attributes_count;
		Attributes* attributes = nullptr;
	};

private:
	Fields() = default;
	std::vector<FieldInfo> m_fields{};
};
