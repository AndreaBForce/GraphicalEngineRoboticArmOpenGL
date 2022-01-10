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
    
        this->emission = glm::vec4(emission,1.0f);
};
void LIB_API Material::setAmbient(glm::vec3 albedo){
    this->ambient = glm::vec4(albedo.r*0.2,albedo.g*0.2,albedo.b*0.2,1.0f);
};

void LIB_API Material::setSpecular(glm::vec3 albedo) {
    this->specular = glm::vec4(albedo.r * 0.4, albedo.g * 0.4, albedo.b * 0.4, 1.0f);
};

void LIB_API Material::setDiffuse(glm::vec3 albedo) {
    this->diffuse = glm::vec4(albedo.r * 0.6, albedo.g * 0.6, albedo.b * 0.6, 1.0f);
};

void LIB_API Material::setShininess(float roughness) {
    this->shininess = ((1 - sqrt(roughness)) * 128);
}

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
