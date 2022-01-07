#include "Mesh.h"
#include <iostream>

Mesh::Mesh()
{
    //ctor
}

Mesh::~Mesh()
{
    //dtor
}

void Mesh::render(){
    std::cout << "redner cube" << std::endl;

    // Set material properties:
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

    // Position and render the cube:
    glm::mat4 transCube = glm::translate(glm::mat4(1.0f), glm::vec3(-20.0f, 0.0f, -60.0f));
    glLoadMatrixf(glm::value_ptr(transCube));
    glutSolidCube(10.0f);
}
