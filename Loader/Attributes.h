#pragma once
#include <cstdint>
#include <cstddef>
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
private:
	Attributes() = default;
	std::vector<RawAttribute> m_attributes {};
};