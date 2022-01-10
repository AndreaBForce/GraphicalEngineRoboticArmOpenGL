#include "Material.h"
#include <GL/freeglut.h>
LIB_API Material::Material() {
}

LIB_API Material::~Material(){
}

void LIB_API Material::setName(char materialName[FILENAME_MAX]){
    this->name = materialName;
};
void LIB_API Material::setEmission(glm::vec3 emission){
        this->emission = emission;
};
void LIB_API Material::setAlbedo(glm::vec3 albedo){
    this->albedo = albedo;
};
void LIB_API Material::setRoughness(float roughness){
    this->roughness = roughness;
};
void LIB_API Material::setMetalness(float metalness){
    this->metalness = metalness;
};
void LIB_API Material::setAlpha(float alpha){
    this->alpha = alpha;
};

void LIB_API Material::setTextureName(char textureName[FILENAME_MAX]){
    strcpy(this->textureName, textureName);
};

void LIB_API Material::setNormalMapName(char NormalMapName[FILENAME_MAX]){
    strcpy(this->normalMapName,NormalMapName);
};
void LIB_API Material::setHeightMapName(char heightMapName[FILENAME_MAX]){
    strcpy(this->heightMapName,heightMapName);
};
void LIB_API Material::setRoughnessMapName(char roughnessMapName[FILENAME_MAX]){
    strcpy(this->roughnessMapName,roughnessMapName);
};
void LIB_API Material::setMetalnessMapName(char metalnessMapName[FILENAME_MAX]){
    strcpy(this->metalnessMapName,metalnessMapName);
};
