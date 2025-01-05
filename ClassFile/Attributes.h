#pragma once
#include <cstdint>
#include <cstddef>
#include <functional>
#include <vector>

#define __ENUMERATE_PREDEFINED_ATTRIBUTES \
	__ENUM(ConstantValue) \
	__ENUM(Code) \
	__ENUM(StackMapTable) \
	__ENUM(BootstrapMethods) \
	__ENUM(NestHost) \
	__ENUM(NestMembers) \
	__ENUM(PermittedSubclasses) \
	__ENUM(Exceptions) \
	__ENUM(InnerClasses) \
	__ENUM(EnclosingMethod) \
	__ENUM(Synthetic) \
	__ENUM(Signature) \
	__ENUM(Record) \
	__ENUM(SourceFile) \
	__ENUM(LineNumberTable) \
	__ENUM(LocalVariableTable) \
	__ENUM(LocalVariableTypeTable) \
	__ENUM(SourceDebugExtension) \
	__ENUM(Deprecated) \
	__ENUM(RuntimeVisibleAnnotations) \
	__ENUM(RuntimeInvisibleAnnotations) \
	__ENUM(RuntimeVisibleParameterAnnotations) \
	__ENUM(RuntimeInvisibleParameterAnnotations) \
	__ENUM(RuntimeVisibleTypeAnnotations) \
	__ENUM(RuntimeInvisibleTypeAnnotations) \
	__ENUM(AnnotationDefault) \
	__ENUM(MethodParameters) \
	__ENUM(Module) \
	__ENUM(ModulePackages) \
	__ENUM(ModuleMainClass)

class ConstantPool;
class Attributes;

struct AttributesCreationResult {
	Attributes* attributes;
	size_t bytes;
};

class Attributes {
public:
	static AttributesCreationResult create(const uint8_t* data, uint16_t attributes_count);
	struct RawAttribute {
		uint16_t attribute_name_index;
		uint32_t attribute_length;
		const uint8_t* info;
	};

	enum class PredefinedAttributeType {
		None = 0,
#define __ENUM(name) name,
		__ENUMERATE_PREDEFINED_ATTRIBUTES
#undef __ENUM
	};

	static const char* predefined_attribute_name(const PredefinedAttributeType type) {
		switch (type) {
#define __ENUM(name) case PredefinedAttributeType::name: return #name;
			__ENUMERATE_PREDEFINED_ATTRIBUTES
#undef __ENUM
			default:
				return "<Invalid PredefinedAttributeType>";
		}
	}

	struct CustomAttribute {
		uint32_t length;
		const uint8_t* data;
	};

	// https://docs.oracle.com/javase/specs/jvms/se23/html/jvms-4.html#jvms-4.7.3
	struct CodeAttribute {
		struct ExceptionTableEntry {
			uint16_t start_pc = 0;
			uint16_t end_pc = 0;
			uint16_t handler_pc = 0;
			uint16_t catch_type = 0;
		};
		uint16_t max_stack = 0;
		uint16_t max_locals = 0;
		uint32_t code_length = 0;
		const uint8_t* code = nullptr;
		uint16_t exception_table_length = 0;
		std::vector<ExceptionTableEntry> exception_table {};
		uint16_t attributes_count = 0;
		Attributes* attributes = nullptr;

		static CodeAttribute from_data(const uint8_t* data);
	};

	// https://docs.oracle.com/javase/specs/jvms/se23/html/jvms-4.html#jvms-4.7.12
	struct LineNumberTable {
		struct LineNumberTableEntry {
			uint16_t start_pc = 0;
			uint16_t line_number = 0;
		};
		uint16_t line_number_table_length = 0;
		std::vector<LineNumberTableEntry> line_number_table {};

		static LineNumberTable from_data(const uint8_t* data);
	};

	struct Attribute {
		PredefinedAttributeType attribute_type;
		union {
			CustomAttribute custom;
			CodeAttribute code;
			LineNumberTable line_number_table;
		};
		~Attribute();
	};

	void for_each(ConstantPool* constant_pool, std::function<void(const char*, Attribute&)> cb) const;

private:
	Attributes() = default;
	std::vector<RawAttribute> m_attributes {};
};