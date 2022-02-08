#include "List.h"
#include <iostream>

#include "Light.h"
#include "Mesh.h"
LIB_API List::List() {
}

LIB_API List::~List() {
    for(auto& element: listObject){
        delete(element);
    }
}

void LIB_API List::renderList(glm::mat4 camera) {
	for (auto& element : getList()) {
		element->render(camera);
	}
}

LIB_API Object* List::getElementByName(const char* name) {
	for (auto& element : getList()) {
		if (element->getName() == name) {
			return element;
		}
	}
	return nullptr;
}

void LIB_API List::addRenderObject(Object* element){

    if((dynamic_cast<Light*>(element))){
        pushFrontOfVec(element);
    }else if((dynamic_cast<Mesh*>(element))){
        pushBackOfVec(element);
    }
}
