#include "Object.h"

static int idCounter = 0;

LIB_API Object::Object() {
	id = idCounter;
	idCounter++;
}

LIB_API Object::~Object(){
    //dtor
}
