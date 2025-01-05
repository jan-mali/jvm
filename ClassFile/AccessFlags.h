#pragma once
#include <cstdint>
#include <cstdio>

class AccessFlags {
public:
	explicit AccessFlags(const uint16_t flags) : m_flags(flags) {}

	[[nodiscard]] bool is_public() const { return (m_flags & 0x0001) != 0; }
	[[nodiscard]] bool is_private() const { return (m_flags & 0x0002) != 0; }
	[[nodiscard]] bool is_protected() const { return (m_flags & 0x0004) != 0; }
	[[nodiscard]] bool is_static() const { return (m_flags & 0x0008) != 0; }
	[[nodiscard]] bool is_final() const { return (m_flags & 0x0010) != 0; }
	[[nodiscard]] bool is_super() const { return (m_flags & 0x0020) != 0; }
	[[nodiscard]] bool is_synchronized() const { return (m_flags & 0x0020) != 0; }
	[[nodiscard]] bool is_volatile() const { return (m_flags & 0x0040) != 0; }
	[[nodiscard]] bool is_bridge() const { return (m_flags & 0x0040) != 0; }
	[[nodiscard]] bool is_transient() const { return (m_flags & 0x0080) != 0; }
	[[nodiscard]] bool is_varargs() const { return (m_flags & 0x0080) != 0; }
	[[nodiscard]] bool is_native() const { return (m_flags & 0x0100) != 0; }
	[[nodiscard]] bool is_interface() const { return (m_flags & 0x0200) != 0; }
	[[nodiscard]] bool is_abstract() const { return (m_flags & 0x0400) != 0; }
	[[nodiscard]] bool is_strict() const { return (m_flags & 0x0800) != 0; }
	[[nodiscard]] bool is_synthetic() const { return (m_flags & 0x1000) != 0; }
	[[nodiscard]] bool is_annotation() const { return (m_flags & 0x2000) != 0; }
	[[nodiscard]] bool is_enum() const { return (m_flags & 0x4000) != 0; }
	[[nodiscard]] bool is_module() const { return (m_flags & 0x8000) != 0; }

	[[nodiscard]] uint16_t flags() const { return m_flags; }

	void dump() const
	{
		bool first = true;
		if (is_public()) {
			if (first) first = false;
			else printf(" ");
			printf("PUBLIC");
		}
		if (is_private()) {
			if (first) first = false;
			else printf(" ");
			printf("PRIVATE");
		}
		if (is_protected()) {
			if (first) first = false;
			else printf(" ");
			printf("PROTECTED");
		}
		if (is_static()) {
			if (first) first = false;
			else printf(" ");
			printf("STATIC");
		}
		if (is_final()) {
			if (first) first = false;
			else printf(" ");
			printf("FINAL");
		}
		if (is_super()) {
			if (first) first = false;
			else printf(" ");
			printf("[CLASS]SUPER");
		}
		if (is_synchronized()) {
			if (first) first = false;
			else printf(" ");
			printf("[METHOD]SYNCHRONIZED");
		}
		if (is_volatile()) {
			if (first) first = false;
			else printf(" ");
			printf("[CLASS]VOLATILE");
		}
		if (is_bridge()) {
			if (first) first = false;
			else printf(" ");
			printf("[METHOD]BRIDGE");
		}
		if (is_transient()) {
			if (first) first = false;
			else printf(" ");
			printf("[CLASS]TRANSIENT");
		}
		if (is_varargs()) {
			if (first) first = false;
			else printf(" ");
			printf("[METHOD]VARARGS");
		}
		if (is_native()) {
			if (first) first = false;
			else printf(" ");
			printf("NATIVE");
		}
		if (is_interface()) {
			if (first) first = false;
			else printf(" ");
			printf("INTERFACE");
		}
		if (is_abstract()) {
			if (first) first = false;
			else printf(" ");
			printf("ABSTRACT");
		}
		if (is_strict()) {
			if (first) first = false;
			else printf(" ");
			printf("STRICT");
		}
		if (is_synthetic()) {
			if (first) first = false;
			else printf(" ");
			printf("SYNTHETIC");
		}
		if (is_annotation()) {
			if (first) first = false;
			else printf(" ");
			printf("ANNOTATION");
		}
		if (is_enum()) {
			if (first) first = false;
			else printf(" ");
			printf("ENUM");
		}
		if (is_module()) {
			if (first) first = false;
			else printf(" ");
			printf("MODULE");
		}
	}

private:
	uint16_t m_flags;
};
