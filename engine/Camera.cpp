#include "Camera.h"
#include <GL/freeglut.h>
#include <iostream>

LIB_API Camera::~Camera()
{
    //dtor
}

glm::mat4 LIB_API Camera::getCameraMat(){

    glm::mat4 finalPosMat = this->getFinalMatrix();

    return glm::lookAt(eye, center, up) * glm::inverse(finalPosMat);
}
