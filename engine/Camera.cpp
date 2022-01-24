#include "Camera.h"
#include <GL/freeglut.h>
#include <iostream>

LIB_API Camera::Camera()
{
    //ctor
}

LIB_API Camera::~Camera()
{
    //dtor
}


void LIB_API Camera::render(glm::mat4 camera){

    std::cout << "render camera" << std::endl;

//    glLoadMatrixf(glm::value_ptr(camera * this->get_final_matrix()));
//
//    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0f);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)));
//    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)));
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
//
//    glutSolidSphere(3.0f, 64.0f, 64.0f);

}

glm::mat4 LIB_API Camera::get_camera_mat(){

    glm::mat4 finalPosMat = this->get_final_matrix();

    return glm::lookAt(eye, center, up) * glm::inverse(finalPosMat);
}
