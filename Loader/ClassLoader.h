#pragma once

class VM;

class ClassLoader {
public:
	virtual ~ClassLoader() = default;

	virtual void load_class(VM* vm, const char* class_name) = 0;
protected:
	std::vector<const char*> m_initiating_loader_for_classes{};
	std::vector<const char*> m_defining_loader_for_classes{};
};