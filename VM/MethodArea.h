#pragma once
#include <vector>

#include "Class.h"

class MethodArea {
public:
	void add_class(Class* _class);
	void dump() const;

private:
	std::vector<Class*> m_classes{};
};
