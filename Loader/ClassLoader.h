#pragma once

class VM;
class Class;

class ClassLoader {
public:
	virtual ~ClassLoader() = default;

	virtual Class* load_class(VM* vm, const char* class_name) = 0;
protected:
	std::vector<uint64_t> m_initiating_loader_for_classes {};
	std::vector<uint64_t> m_defining_loader_for_classes {};
};