#pragma once
#include <cstdint>

class Method;
class Class;

struct CodeAddress {
	Class* _class = nullptr;
	Method* method = nullptr;
	uint16_t instruction = 0;
};
