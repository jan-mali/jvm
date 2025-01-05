#include "ConstantPool.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

ConstantPoolCreationResult ConstantPool::create(const uint8_t* data, const uint16_t constant_pool_count) {
    auto* constant_pool = new ConstantPool();
    const uint8_t* ptr = data;

    for (uint16_t i = 0; i < constant_pool_count; i++) {
        auto tag = static_cast<Tag>(*ptr++);

        ConstantPoolEntry entry = {};
        entry.tag = tag;

        switch (tag) {
            case Tag::Utf8: {
                uint16_t length = ptr[0] << 8 | ptr[1];
                ptr += sizeof(uint16_t);
                const char* str = strndup(reinterpret_cast<const char *>(ptr), length);
                entry.utf8 = Utf8(tag, length, str);
                ptr += length;
                break;
            }
            case Tag::Class: {
                uint16_t name_index = ptr[0] << 8 | ptr[1];
                ptr += sizeof(uint16_t);
                entry._class = Class(tag, name_index);
                break;
            }
            case Tag::Methodref: {
                uint16_t class_index = ptr[0] << 8 | ptr[1];
                ptr += sizeof(uint16_t);
                uint16_t name_and_type_index = ptr[0] << 8 | ptr[1];
                ptr += sizeof(uint16_t);
                entry.method_ref = MethodRef(tag, class_index, name_and_type_index);
                break;
            }
            case Tag::NameAndType: {
                uint16_t name_index = ptr[0] << 8 | ptr[1];
                ptr += sizeof(uint16_t);
                uint16_t descriptor_index = ptr[0] << 8 | ptr[1];
                ptr += sizeof(uint16_t);
                entry.name_and_type = NameAndType(tag, name_index, descriptor_index);
                break;
            }
            default:
                // TODO: Implement the missing tag
                printf("TODO: Implement tag %s\n", tag_name(tag));
                abort();
        }

        constant_pool->m_constant_pool_entries.push_back(entry);
    }

    const size_t bytes = ptr - data;
    return {
        .pool = constant_pool,
        .bytes = bytes,
    };
}

void ConstantPool::dump(size_t indent) const {
    size_t i = 0;
    for (auto entry : m_constant_pool_entries) {
        for (size_t j = 0; j < indent; j++) {
            printf("\t");
        }
        printf("%3llu. %s ", ++i, tag_name(entry.tag));
        switch (entry.tag) {
            case Tag::Class: {
                const uint16_t name_index = entry._class.name_index;
                const char* name = m_constant_pool_entries[name_index - 1].utf8.bytes;
                printf("[%s]", name );
                break;
            }
            case Tag::Utf8: {
                printf("len=%hu bytes=\"%s\"", entry.utf8.length, entry.utf8.bytes);
                break;
            }
            case Tag::Methodref: {
                const uint16_t class_index = entry.method_ref.class_index;
                const Class _class = m_constant_pool_entries[class_index - 1]._class;
                const char* class_name = m_constant_pool_entries[_class.name_index - 1].utf8.bytes;

                const uint16_t name_and_type_index = entry.method_ref.name_and_type_index;
                const NameAndType name_and_type = m_constant_pool_entries[name_and_type_index - 1].name_and_type;
                const char* name = m_constant_pool_entries[name_and_type.name_index - 1].utf8.bytes;
                const char* descriptor = m_constant_pool_entries[name_and_type.descriptor_index - 1].utf8.bytes;

                printf("class=[%s] name=[%s] descriptor=[%s]", class_name, name, descriptor);
                break;
            }
            case Tag::NameAndType: {
                const uint16_t name_index = entry.name_and_type.name_index;
                const char* name = m_constant_pool_entries[name_index - 1].utf8.bytes;
                const uint16_t descriptor_index = entry.name_and_type.descriptor_index;
                const char* descriptor = m_constant_pool_entries[descriptor_index - 1].utf8.bytes;
                printf("[%s] [%s]", name, descriptor);
                break;
            }
            default:
                printf("<TODO: Extra data>");
                break;
        }
        printf("\n");
    }
}
