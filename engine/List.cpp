#include "List.h"
#include <iostream>
LIB_API List::List() {
}

LIB_API List::~List() {
}

void LIB_API List::render_list() {
	for (auto& element : get_list()) {
		element->render();
	}
}

LIB_API Object* List::get_element_by_name(char* name) {
	for (auto& element : get_list()) {
		if (element->get_name() == name) {
			return element;
		}
	}
	return nullptr;
}