#ifndef TEXTURE_H
#define TEXTURE_H
#include "Object.h"
#include "Utils.h"

class LIB_API Texture : public Object {
public:
	Texture();
	~Texture();
	void render() {};
};

#endif // TEXTURE_H