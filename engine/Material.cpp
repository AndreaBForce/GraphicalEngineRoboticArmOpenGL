#include "Material.h"
#include <GL/freeglut.h>
#include <iostream>
LIB_API Material::Material() {
}

LIB_API Material::~Material(){
}

void LIB_API Material::setEmission(glm::vec3 emission){
        this->emission = glm::vec4(emission,1.0f);
}

void LIB_API Material::setAmbient(glm::vec3 albedo){
    this->ambient = glm::vec4(albedo.r*0.2,albedo.g*0.2,albedo.b*0.2,1.0f);
}

void LIB_API Material::setSpecular(glm::vec3 albedo) {
    this->specular = glm::vec4(albedo.r * 0.4, albedo.g * 0.4, albedo.b * 0.4, 1.0f);
}

void LIB_API Material::setDiffuse(glm::vec3 albedo) {
    this->diffuse = glm::vec4(albedo.r * 0.6, albedo.g * 0.6, albedo.b * 0.6, 1.0f);
}

void LIB_API Material::setShininess(float roughness) {
    this->shininess = ((1 - sqrt(roughness)) * 128);
}

void LIB_API Material::setTexture(char textureName[FILENAME_MAX]){
    if(textureName != NULL){
        Texture* texture = new Texture(textureName);
        this->texture = texture;
    }else
        this->texture = nullptr;
}

void LIB_API Material::render(glm::mat4 camera){

    if(texture != nullptr){
        texture->render(camera);
    }

    // Set material properties:
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(this->emission));
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(this->ambient));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(this->diffuse));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(this->specular));

}
