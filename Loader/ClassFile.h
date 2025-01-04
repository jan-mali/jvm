#pragma once
#include <cstdint>

#include "AccessFlags.h"
#include "ConstantPool.h"
#include "Fields.h"
#include "Methods.h"

class ClassFile {
public:
    static ClassFile* create(const uint8_t* data);
    static ClassFile* create_from_path(const char* path);
private:
    ClassFile() = default;
    uint16_t m_minor_version = 0;
    uint16_t m_major_version = 0;
    uint16_t m_constant_pool_count = 0;
    ConstantPool* m_constant_pool = nullptr;
    AccessFlags m_access_flags { 0 };
    uint16_t this_class = 0;
    uint16_t super_class = 0;
    uint16_t interfaces_count = 0;
    uint16_t* interfaces = nullptr;
    uint16_t fields_count = 0;
    Fields* m_fields = nullptr;
    uint16_t methods_count = 0;
    Methods* m_methods = nullptr;
    uint16_t attributes_count = 0;
    Attributes* m_attributes = nullptr;
};
