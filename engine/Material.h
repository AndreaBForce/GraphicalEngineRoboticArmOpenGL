#ifndef MATERIAL_H
#define MATERIAL_H
#include "Object.h"
#include "Texture.h"
#include "Utils.h"

class LIB_API Material : public Object {
public:
    Material();
    virtual ~Material();
    void render() {};


    void setName(char materialName[FILENAME_MAX]);
    void setEmission(glm::vec3 emission);
    void setAmbient(glm::vec3 ambient);
    void setSpecular(glm::vec3 specular);
    void setDiffuse(glm::vec3 diffuse);

    void setShininess(float shininess);

    void setTextureName(char textureName[FILENAME_MAX]);
    void setNormalMapName(char NormalMapName[FILENAME_MAX]);
    void setHeightMapName(char heightMapName[FILENAME_MAX]);
    void setRoughnessMapName(char roughnessMapName[FILENAME_MAX]);
    void setMetalnessMapName(char metalnessMapName[FILENAME_MAX]);

    //todo add material properties
private:
    Texture texture;

    char* name;
    //Campi materiale

    glm::vec4 emission;
    glm::vec4 ambient;
    glm::vec4 specular;
    glm::vec4 diffuse;

    float shininess;

    char textureName[FILENAME_MAX];
    char normalMapName[FILENAME_MAX];
    char heightMapName[FILENAME_MAX];
    char roughnessMapName[FILENAME_MAX];
    char metalnessMapName[FILENAME_MAX];
};


#endif // MATERIAL_H
