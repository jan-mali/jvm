#pragma once
#include <cstdint>
#include <vector>

// https://docs.oracle.com/javase/specs/jvms/se23/html/jvms-4.html#jvms-4.4-140
#define __ENUMERATE_CONSTANT_POOL_TAGS \
    __ENUM(Invalid, 0) \
    __ENUM(Class, 7) \
    __ENUM(Fieldref, 9) \
    __ENUM(Methodref, 10) \
    __ENUM(InterfaceMethodref, 11) \
    __ENUM(String, 8) \
    __ENUM(Integer, 3) \
    __ENUM(Float, 4) \
    __ENUM(Long, 5) \
    __ENUM(Double, 6) \
    __ENUM(NameAndType, 12) \
    __ENUM(Utf8, 1) \
    __ENUM(MethodHandle, 15) \
    __ENUM(MethodType, 16) \
    __ENUM(Dynamic, 17) \
    __ENUM(InvokeDynamic, 18) \
    __ENUM(Module, 19) \
    __ENUM(Package, 20)

class ConstantPool;

struct ConstantPoolCreationResult {
    ConstantPool* pool;
    size_t bytes;
};

class ConstantPool {
public:
    static ConstantPoolCreationResult create(const uint8_t* data, uint16_t constant_pool_count);

    void dump(size_t indent) const;

    enum class Tag : uint8_t {
#define __ENUM(name, value) name = value,
        __ENUMERATE_CONSTANT_POOL_TAGS
#undef __ENUM
    };

    static const char* tag_name(const Tag tag) {
        switch (tag) {
#define __ENUM(name, value) case Tag::name: return #name;
            __ENUMERATE_CONSTANT_POOL_TAGS
#undef __ENUM
            default:
                return "<Unknown tag>";
        }
    }

    struct ConstantPoolEntryBase {
        Tag tag;
    };

    struct Class : ConstantPoolEntryBase {
        Class(const Tag tag, const uint16_t name_index) : ConstantPoolEntryBase(tag), name_index(name_index){}
        uint16_t name_index;
    };

    struct FieldRef : ConstantPoolEntryBase {
        FieldRef(const Tag tag, const uint16_t class_index, const uint16_t name_and_type_index) : ConstantPoolEntryBase(tag), class_index(class_index), name_and_type_index(name_and_type_index) {}
        uint16_t class_index;
        uint16_t name_and_type_index;
    };

    struct MethodRef : ConstantPoolEntryBase {
        MethodRef(const Tag tag, const uint16_t class_index, const uint16_t name_and_type_index) : ConstantPoolEntryBase(tag), class_index(class_index), name_and_type_index(name_and_type_index) {}
        uint16_t class_index;
        uint16_t name_and_type_index;
    };

    struct InterfaceMethodRef : ConstantPoolEntryBase {
        InterfaceMethodRef(const Tag tag, const uint16_t class_index, const uint16_t name_and_type_index) : ConstantPoolEntryBase(tag), class_index(class_index), name_and_type_index(name_and_type_index) {}
        uint16_t class_index;
        uint16_t name_and_type_index;
    };

    struct String : ConstantPoolEntryBase {
        String(const Tag tag, const uint16_t string_index) : ConstantPoolEntryBase(tag), string_index(string_index) {}
        uint16_t string_index;
    };

    struct Integer : ConstantPoolEntryBase {
        Integer(const Tag tag, const uint32_t bytes) : ConstantPoolEntryBase(tag), bytes(bytes) {}
        uint32_t bytes;
        [[nodiscard]] int32_t value() const {
            const auto b1 = static_cast<uint8_t>(bytes >> 24);
            const auto b2 = static_cast<uint8_t>(bytes >> 16);
            const auto b3 = static_cast<uint8_t>(bytes >> 8);
            const auto b4 = static_cast<uint8_t>(bytes >> 0);
            return (b1 << 24) | (b2 << 16) | (b3 << 8) | (b4 << 0);
        };
    };

    struct Float : ConstantPoolEntryBase {
        Float(const Tag tag, const uint32_t bytes) : ConstantPoolEntryBase(tag), bytes(bytes) {}
        uint32_t bytes;
        [[nodiscard]] float value() const; // TODO
    };

    struct Long : ConstantPoolEntryBase {
        Long(const Tag tag, const uint32_t high_bytes, const uint32_t low_bytes) : ConstantPoolEntryBase(tag), high_bytes(high_bytes), low_bytes(low_bytes) {}
        uint32_t high_bytes;
        uint32_t low_bytes;
        [[nodiscard]] int64_t value() const {
	        return static_cast<int64_t>(high_bytes) << 32 | static_cast<int64_t>(low_bytes);
        }
    };

    struct Double : ConstantPoolEntryBase {
        Double(const Tag tag, const uint32_t high_bytes, const uint32_t low_bytes) : ConstantPoolEntryBase(tag), high_bytes(high_bytes), low_bytes(low_bytes) {}
        uint32_t high_bytes;
        uint32_t low_bytes;
        [[nodiscard]] double value() const; // TODO
    };

    struct NameAndType : ConstantPoolEntryBase {
        NameAndType(const Tag tag, const uint16_t name_index, const uint16_t descriptor_index) : ConstantPoolEntryBase(tag), name_index(name_index), descriptor_index(descriptor_index) {}
        uint16_t name_index;
        uint16_t descriptor_index;
    };

    struct Utf8 : ConstantPoolEntryBase {
        Utf8(const Tag tag, const uint16_t length, const char* bytes) : ConstantPoolEntryBase(tag), length(length), bytes(bytes) {}
        uint16_t length;
        const char* bytes;
    };

    struct MethodHandle : ConstantPoolEntryBase {
        MethodHandle(const Tag tag, const uint16_t reference_kind, const uint16_t reference_index) : ConstantPoolEntryBase(tag), reference_kind(reference_kind), reference_index(reference_index) {}
        uint16_t reference_kind;
        uint16_t reference_index;
    };

    struct MethodType : ConstantPoolEntryBase {
        MethodType(const Tag tag, const uint16_t descriptor_index) : ConstantPoolEntryBase(tag), descriptor_index(descriptor_index) {}
        uint16_t descriptor_index;
    };

    struct Dynamic : ConstantPoolEntryBase {
        Dynamic(const Tag tag, const uint16_t bootstrap_method_attr_index, const uint16_t name_and_type_index) : ConstantPoolEntryBase(tag), bootstrap_method_attr_index(bootstrap_method_attr_index), name_and_type_index(name_and_type_index) {}
        uint16_t bootstrap_method_attr_index;
        uint16_t name_and_type_index;
    };

    struct InvokeDynamic : ConstantPoolEntryBase {
        InvokeDynamic(const Tag tag, const uint16_t bootstrap_method_attr_index, const uint16_t name_and_type_index) : ConstantPoolEntryBase(tag), bootstrap_method_attr_index(bootstrap_method_attr_index), name_and_type_index(name_and_type_index) {}
        uint16_t bootstrap_method_attr_index;
        uint16_t name_and_type_index;
    };

    struct Module : ConstantPoolEntryBase {
        Module(const Tag tag, const uint16_t name_index) : ConstantPoolEntryBase(tag), name_index(name_index) {}
        uint16_t name_index;
    };

    struct Package : ConstantPoolEntryBase {
        Package(const Tag tag, const uint16_t name_index) : ConstantPoolEntryBase(tag), name_index(name_index) {}
        uint16_t name_index;
    };

    struct ConstantPoolEntry {
        Tag tag;
        union {
            Class _class;
            FieldRef field_ref;
            MethodRef method_ref;
            InterfaceMethodRef interface_method_ref;
            String string;
            Integer integer;
            Float _float;
            Long _long;
            Double _double;
            NameAndType name_and_type;
            Utf8 utf8;
            MethodHandle method_handle;
            MethodType method;
            Dynamic dynamic;
            InvokeDynamic invoke_dynamic;
            Module module;
            Package package;
        };
    };

    [[nodiscard]] ConstantPoolEntry get_index(const uint16_t index) const {
        return m_constant_pool_entries[index];
    }

    [[nodiscard]] ConstantPoolEntry get_jvm_index(const uint16_t index) const {
        return get_index(index - 1);
    }

private:
    ConstantPool() = default;

    std::vector<ConstantPoolEntry> m_constant_pool_entries {};
};

#undef __ENUMERATE_CONSTANT_POOL_TAGS