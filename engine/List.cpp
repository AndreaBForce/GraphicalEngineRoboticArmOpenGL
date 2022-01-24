#include "List.h"
#include <iostream>

#include "Light.h"
#include "Mesh.h"
LIB_API List::List() {
}

LIB_API List::~List() {
}

void LIB_API List::render_list(glm::mat4 camera) {
	for (auto& element : get_list()) {
		element->render(camera);
	}
}

LIB_API Object* List::get_element_by_name(const char* name) {
	for (auto& element : get_list()) {
		if (element->get_name() == name) {
			return element;
		}
	}
	return nullptr;
}

void LIB_API List::addRenderObject(Object* element){

    if((dynamic_cast<Light*>(element))){
        put_front_of_vec(element);
    }else if((dynamic_cast<Mesh*>(element))){
        put_back_of_vec(element);
    }
}
