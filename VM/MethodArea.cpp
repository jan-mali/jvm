#include "MethodArea.h"

#include <cstdio>

void MethodArea::add_class(Class* _class) {
	m_classes.push_back(_class);
}

void MethodArea::dump() const {
	printf("MethodArea::dump()\n");
	for (auto _class: m_classes) {
		_class->dump();
	}
}
