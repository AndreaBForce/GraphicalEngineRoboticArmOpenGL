#include "Light.h"
#include <iostream>

Light::Light() {
	//ctor
}

Light::~Light() {
	//dtor
}

void Light::setViewMatrix(glm::mat4 matrix){
    this->view_matrix = matrix;
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
   glm::vec4 objectCoordPosition(0.0f, 0.0f, 0.0f, 1.0f);
   glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(objectCoordPosition));
   glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(Light::ambient));
   glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(Light::diffuse));
   glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(Light::specular));
}

