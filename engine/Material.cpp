#include "Material.h"

Material::Material() {
}

Material::~Material(){
}

void Material::setName(char materialName[FILENAME_MAX]){
    this->name = materialName;
};
void Material::setEmission(glm::vec3 emission){
        this->emission = emission;
};
void Material::setAlbedo(glm::vec3 albedo){
    this->albedo = albedo;
};
void Material::setRoughness(float roughness){
    this->roughness = roughness;
};
void Material::setMetalness(float metalness){
    this->metalness = metalness;
};
void Material::setAlpha(float alpha){
    this->alpha = alpha;
};

void Material::setTextureName(char textureName[FILENAME_MAX]){
    strcpy(this->textureName, textureName);
};

void Material::setNormalMapName(char NormalMapName[FILENAME_MAX]){
    strcpy(this->normalMapName,NormalMapName);
};
void Material::setHeightMapName(char heightMapName[FILENAME_MAX]){
    strcpy(this->heightMapName,heightMapName);
};
void Material::setRoughnessMapName(char roughnessMapName[FILENAME_MAX]){
    strcpy(this->roughnessMapName,roughnessMapName);
};
void Material::setMetalnessMapName(char metalnessMapName[FILENAME_MAX]){
    strcpy(this->metalnessMapName,metalnessMapName);
};
