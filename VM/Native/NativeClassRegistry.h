#pragma once
#include <cstdint>
#include <unordered_map>

#include "NativeClass.h"

class NativeClassRegistry {
public:
	void register_class(NativeClass* native_class);
	NativeClass* get_native_class(const char* name);
private:
	std::unordered_map<uint64_t, NativeClass*> m_classes {};
};