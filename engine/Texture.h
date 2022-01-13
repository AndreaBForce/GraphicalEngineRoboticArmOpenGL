#ifndef TEXTURE_H
#define TEXTURE_H
#include "Object.h"
#include "Utils.h"

class LIB_API Texture : public Object {
public:
	Texture();
	~Texture();
	void render(glm::mat4 camera) {};
};

#endif // TEXTURE_H
