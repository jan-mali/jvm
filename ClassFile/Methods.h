#pragma once
#include <cstdint>
#include <vector>

#include "AccessFlags.h"
#include "Attributes.h"

class Methods;

struct MethodsCreationResult {
	Methods* methods;
	size_t bytes;
};

class Methods {
public:
	static MethodsCreationResult create(const uint8_t* data, uint16_t fields_count);

	struct MethodInfo {
		AccessFlags access_flags { 0 };
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t attributes_count;
		Attributes* attributes = nullptr;
	};

	void for_each(std::function<void(MethodInfo)> cb);

private:
	Methods() = default;
	std::vector<MethodInfo> m_methods {};
};
