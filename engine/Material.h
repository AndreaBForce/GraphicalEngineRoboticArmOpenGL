#ifndef MATERIAL_H
#define MATERIAL_H
#include "Object.h"
#include "Texture.h"
#include "Utils.h"

class LIB_API Material : public Object {
public:
    Material();
    virtual ~Material();
    void render(glm::mat4 camera) override;

    void setEmission(glm::vec3 emission);
    void setAmbient(glm::vec3 ambient);
    void setSpecular(glm::vec3 specular);
    void setDiffuse(glm::vec3 diffuse);

    void setShininess(float shininess);

    void setTextureName(char textureName[FILENAME_MAX]);

private:
    Texture* texture;

    glm::vec4 emission;
    glm::vec4 ambient;
    glm::vec4 specular;
    glm::vec4 diffuse;

    float shininess;

    char textureName[FILENAME_MAX];
};


#endif // MATERIAL_H
