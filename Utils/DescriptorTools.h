#pragma once
#include <cassert>
#include <cstring>
#include <vector>

#include "../VM/Variable.h"

// FIXME: Refactor this
// NOTE: This file has been "borrowed" from by older JVM implementation

struct FieldDescriptor {
	Variable::Type var_type{};
	char* reference_name;
	Variable::Type simple_array_type{};
};

struct MethodDescriptor {
	std::vector<FieldDescriptor> params{};
	FieldDescriptor return_type{};
};

class DescriptorTools {
public:
	static MethodDescriptor parse_method(const char* descriptor) {
		enum class MethodDescriptorParsingState {
			Start,
			Params,
			ReturnValue
		};
		assert(descriptor);
		const char* ptr = descriptor;
		auto state = MethodDescriptorParsingState::Start;
		MethodDescriptor ret{};
		do {
			const char c = *ptr;
			switch (state) {
			case MethodDescriptorParsingState::Start:
				if (c == '(')
					state = MethodDescriptorParsingState::Params;
				break;
			case MethodDescriptorParsingState::Params: {
				if (c == ')') {
					state = MethodDescriptorParsingState::ReturnValue;
					break;
				}
				size_t offset = 0;
				FieldDescriptor fd = parse_field(ptr, &offset);
				ret.params.push_back(fd);
				if (fd.var_type == Variable::Type::Reference)
					ptr += offset - 1;
				break;
			}
			case MethodDescriptorParsingState::ReturnValue:
				ret.return_type = parse_field(ptr);
				return ret;
			default:
				assert(false);
			}
		} while (*ptr++ != 0);
		return ret;
	}
	static FieldDescriptor parse_field(const char* descriptor, size_t* offset = nullptr) {
		assert(descriptor);
		char descriptor_start = descriptor[0];
		FieldDescriptor ret{};
		// https://docs.oracle.com/javase/specs/jvms/se23/html/jvms-4.html#jvms-4.3.2
		switch (descriptor_start) {
		case 'B':
			ret.var_type = Variable::Type::Byte;
			return ret;
		case 'C':
			ret.var_type = Variable::Type::Char;
			return ret;
		case 'D':
			ret.var_type = Variable::Type::Double;
			return ret;
		case 'F':
			ret.var_type = Variable::Type::Float;
			return ret;
		case 'I':
			ret.var_type = Variable::Type::Int;
			return ret;
		case 'J':
			ret.var_type = Variable::Type::Long;
			return ret;
		case 'L':
			ret.var_type = Variable::Type::Reference;
			break;
		case 'S':
			ret.var_type = Variable::Type::Short;
			return ret;
		case 'Z':
			ret.var_type = Variable::Type::Boolean;
			return ret;
		case 'V':
			ret.var_type = Variable::Type::Invalid;
			return ret;
		case '[':
			ret.var_type = Variable::Type::Reference;
			break;
		default:
			assert(false);
		}
		if (descriptor[0] == '[' && descriptor[1] != 'L') {
			if (descriptor[1] == 'B')
				ret.simple_array_type = Variable::Type::Byte;
			if (descriptor[1] == 'C')
				ret.simple_array_type = Variable::Type::Char;
			if (descriptor[1] == 'D')
				ret.simple_array_type = Variable::Type::Double;
			if (descriptor[1] == 'F')
				ret.simple_array_type = Variable::Type::Float;
			if (descriptor[1] == 'I')
				ret.simple_array_type = Variable::Type::Int;
			if (descriptor[1] == 'J')
				ret.simple_array_type = Variable::Type::Long;
			if (descriptor[1] == 'S')
				ret.simple_array_type = Variable::Type::Short;
			if (descriptor[1] == 'Z')
				ret.simple_array_type = Variable::Type::Boolean;
			return ret;
		}
		const char* ptr = &descriptor[2];
		ret.reference_name = new char[512];
		memset(ret.reference_name, 0, 512);
		size_t cur = 0;
		do {
			memcpy(ret.reference_name + cur, ptr, 1);
			ret.reference_name[++cur] = 0;
		} while (*ptr++ != ';');
		if (offset) {
			*offset += cur + 2;
		}
		return ret;
	}
};
