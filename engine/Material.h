#ifndef MATERIAL_H
#define MATERIAL_H
#include "Object.h"
#include "Texture.h"
#include "Utils.h"

class LIB_API Material : public Object {
public:
    Material();
    ~Material();
    void render(glm::mat4 camera) override;

    void setEmission(glm::vec3 emission);
    void setAmbient(glm::vec3 ambient);
    void setSpecular(glm::vec3 specular);
    void setDiffuse(glm::vec3 diffuse);
    void setShininess(float shininess);
    void setTexture(char textureName[FILENAME_MAX]);

    bool hasTexture(){return texture != nullptr;}

    glm::vec4 getEmission();
    glm::vec4 getAmbient();
    glm::vec4 getSpecular();
    glm::vec4 getDiffuse();
    float getShiness();

private:
    Texture* texture;

    glm::vec4 emission;
    glm::vec4 ambient;
    glm::vec4 specular;
    glm::vec4 diffuse;

    float shininess;
};


#endif // MATERIAL_H
