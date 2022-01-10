#include "Light.h"
#include <iostream>

Light::Light() {
	//ctor
}

Light::~Light() {
	//dtor
}

void Light::setPosition(glm::vec3 position){
    this->position = position;
}

void Light::setAmbient(glm::vec4 ambient){
    this->ambient = ambient;
}

void Light::setDiffuse(glm::vec4 diffuse){
    this->diffuse = diffuse;
}

void Light::setSpecular(glm::vec4 specular){
    this->specular = specular;
}

void Light::setDirection(glm::vec3 direction){
    this->direction = direction;
}

void Light::setCutoff(float cutoff){
    this->cutoff = cutoff;
}

void Light::setLightType(lightType type){
    this->type = type;
}

void Light::render() {
    std::cout << "render light" << std::endl;

    // Set light position:
   glm::mat4 transLight = glm::translate(glm::mat4(1.0f), this->position);
   glLoadMatrixf(glm::value_ptr(transLight));

   // Draw a small emissive sphere to show light position:
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec4(1.0f)));
   glutSolidSphere(0.5, 64, 64);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec4(0.0f)));

   // Light position is set to object coordinates and is modified by the current OpenGL matrix (as with any other object):
   //glm::vec4 objectCoordPosition(0.0f, 0.0f, 0.0f, 1.0f);

   glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(Light::ambient));
   glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(Light::diffuse));
   glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(Light::specular));

   glm::vec4 objectCoordPosition;
   switch(this->type){
    case lightType::DIRECTIONAL:
        objectCoordPosition = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case lightType::OMNI:
        objectCoordPosition = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &cutoff);
        break;
    case lightType::SPOT:
        objectCoordPosition = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &cutoff);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, glm::value_ptr(this->direction));
        break;
    default:
        break;
   }

   glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(objectCoordPosition));
}

