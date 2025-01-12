#pragma once

#include <cstddef>
#include <cstdint>

class HashTools {
public:
	static uint64_t fnv1a_hash(const uint8_t* data, const size_t length) {
		constexpr uint64_t fnv_prime = 1099511628211u;
		constexpr uint64_t fnv_offset_basis = 14695981039346656037u;

		uint64_t hash = fnv_offset_basis;
		for (size_t i = 0; i < length; ++i) {
			hash ^= data[i];
			hash *= fnv_prime;
		}
		return hash;
	}
};
