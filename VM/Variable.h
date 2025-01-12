#pragma once

#include <cstdint>

#define __ENUMERATE_VARIABLE_TYPES \
	__ENUM(Boolean)                \
	__ENUM(Byte)                   \
	__ENUM(Char)                   \
	__ENUM(Short)                  \
	__ENUM(Int)                    \
	__ENUM(Float)                  \
	__ENUM(Reference)              \
	__ENUM(ReturnAddress)          \
	__ENUM(Long)                   \
	__ENUM(Double)

struct Variable {
	enum class Type {
		Invalid = 0,
#define __ENUM(type) type,
		__ENUMERATE_VARIABLE_TYPES
#undef __ENUM
	};

	static const char* type_name(Type type) {
		switch (type) {
#define __ENUM(type) \
	case Type::type: \
		return #type;
			__ENUMERATE_VARIABLE_TYPES
#undef __ENUM
		default:
			return "Invalid";
		}
	}

	[[nodiscard]] uint8_t computational_type() const {
		switch (type) {
		case Type::Double:
		case Type::Long:
			return 2;
		default:
			return 1;
		}
	}

	[[nodiscard]] uint8_t stack_depth() const {
		return computational_type();
	}

	Type type = Type::Invalid;
	int64_t value = 0; // FIXME: Maybe a union would be better?
};

#undef __ENUMERATE_VARIABLE_TYPES
