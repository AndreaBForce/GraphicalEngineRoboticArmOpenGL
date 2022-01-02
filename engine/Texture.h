#ifndef TEXTURE_H
#define TEXTURE_H
#include "Object.h"

class Texture : public Object {
public:
	Texture();
	~Texture();
	void render() {};
};

#endif // TEXTURE_H