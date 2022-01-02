#ifndef MATERIAL_H
#define MATERIAL_H
#include "Object.h"
#include "Texture.h"

class Material : public Object {
public:
    Material();
    virtual ~Material();
    void render() {};

    //todo add material properties
private:
    Texture texture;
};

#endif // MATERIAL_H