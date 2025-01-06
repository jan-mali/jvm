#include "NativeClassRegistry.h"

#include <cassert>
#include <cstring>

#include "../../Utils/HashTools.h"

void NativeClassRegistry::register_class(NativeClass* native_class) {
	assert(native_class);
	const char* name = native_class->name();
	const uint64_t hash = HashTools::fnv1a_hash(reinterpret_cast<const uint8_t*>(name), strlen(name));
	assert(!m_classes.contains(hash));
	m_classes[hash] = native_class;
}

NativeClass* NativeClassRegistry::get_native_class(const char* name) {
	const uint64_t hash = HashTools::fnv1a_hash(reinterpret_cast<const uint8_t*>(name), strlen(name));
	if (m_classes.contains(hash)) {
		return m_classes[hash];
	}
	return nullptr;
}
