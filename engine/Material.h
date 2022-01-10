#ifndef MATERIAL_H
#define MATERIAL_H
#include "Object.h"
#include "Texture.h"

class Material : public Object {
public:
    Material();
    virtual ~Material();
    void render() {};


    void setName(char materialName[FILENAME_MAX]);
    void setEmission(glm::vec3 emission);
    void setAlbedo(glm::vec3 albedo);
    void setRoughness(float roughness);
    void setMetalness(float metalness);
    void setAlpha(float alpha);

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
    glm::vec3 emission;
    glm::vec3 albedo;
    float roughness;
    float metalness;
    float alpha;
    char textureName[FILENAME_MAX];
    char normalMapName[FILENAME_MAX];
    char heightMapName[FILENAME_MAX];
    char roughnessMapName[FILENAME_MAX];
    char metalnessMapName[FILENAME_MAX];
};


#endif // MATERIAL_H
