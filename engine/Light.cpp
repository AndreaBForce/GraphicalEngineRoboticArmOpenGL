#include "Light.h"
#include <iostream>
#include <GL/freeglut.h>

//define static variable
int Light::lightsCnt = 0;


LIB_API Light::Light() {

    if(lightsCnt < MAX_LIGHTS){

        switch(lightsCnt){
            case 0:
                lightNr = LIGHT0;
                break;
            case 1:
                lightNr = LIGHT1;
                break;
            default:
                break;
        }


        lightsCnt++;
    }else{
        lightNr = 0;
        std::cerr << "MAX " << MAX_LIGHTS << " LIGHTS MANAGEABLE" << std::endl;
    }

	//ctor
}

LIB_API Light::~Light() {
    std::cout << "Light dtor" << std::endl;
    lightsCnt--;
}

void LIB_API Light::setAmbient(glm::vec4 ambient){
    this->ambient = ambient;
}

void LIB_API Light::setDiffuse(glm::vec4 diffuse){
    this->diffuse = diffuse;
}

void LIB_API Light::setSpecular(glm::vec4 specular){
    this->specular = specular;
}

void LIB_API Light::setDirection(glm::vec3 direction){
    this->direction = direction;
}

void LIB_API Light::setCutoff(float cutoff){
    this->cutoff = cutoff;
}

void LIB_API Light::setLightType(lightType type){
    this->type = type;
}

glm::vec4 LIB_API Light::getAmbient() {
    return this->ambient;
}

glm::vec4 LIB_API Light::getDiffuse() {
    return this->diffuse;
}

glm::vec4 LIB_API Light::getSpecular() {
    return this->specular;
}

glm::vec3 LIB_API Light::getDirection() {
    return this->direction;
}

float LIB_API Light::getCutoff() {
    return this->cutoff;
}

lightType LIB_API Light::getLightType() {
    return this->type;
}

void LIB_API Light::render(glm::mat4 camera) {

    if(lightNr == 0)
        return;

    // Set light position:
   glLoadMatrixf(glm::value_ptr(camera * this->getFinalMatrix()));

   // Light position is set to object coordinates and is modified by the current OpenGL matrix (as with any other object):
   glLightfv(lightNr, GL_AMBIENT, glm::value_ptr(Light::ambient));
   glLightfv(lightNr, GL_DIFFUSE, glm::value_ptr(Light::diffuse));
   glLightfv(lightNr, GL_SPECULAR, glm::value_ptr(Light::specular));

   glm::vec4 objectCoordPosition;
   switch(this->type){
    case lightType::DIRECTIONAL:
        objectCoordPosition = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case lightType::OMNI:
        objectCoordPosition = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glLightfv(lightNr, GL_SPOT_CUTOFF, &cutoff);
        break;
    case lightType::SPOT:
        objectCoordPosition = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glLightfv(lightNr, GL_SPOT_CUTOFF, &cutoff);
        glLightfv(lightNr, GL_SPOT_DIRECTION, glm::value_ptr(this->direction));
        break;
    default:
        break;
   }

   glLightfv(lightNr, GL_POSITION, glm::value_ptr(objectCoordPosition));
}

