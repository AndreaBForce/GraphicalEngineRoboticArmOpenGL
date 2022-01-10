#include "Mesh.h"
#include "Utils.h"
#include <iostream>
#include <GL/freeglut.h>

LIB_API Mesh::Mesh()
{
    //ctor
}

LIB_API Mesh::~Mesh()
{
    //dtor
}

LIB_API Material* Mesh::get_material(){
    return material;
}

void LIB_API Mesh::set_matrix(glm::mat4 mesh_matrix){
    matrix = mesh_matrix;
}

void LIB_API Mesh::set_bBoxMin(glm::vec3 mesh_bBoxMin){
    bBoxMin = mesh_bBoxMin;
}

void LIB_API Mesh::set_bBoxMax(glm::vec3 mesh_bBoxMax){
    bBoxMax = mesh_bBoxMax;
}

void LIB_API Mesh::set_radius(float mesh_radius){
    radius = mesh_radius;
}

void LIB_API Mesh::set_children(unsigned int mesh_children){
    children = mesh_children;
}

void LIB_API Mesh::set_subtype(char mesh_subtypeName[FILENAME_MAX]){
    strcpy(subtypeName, mesh_subtypeName);
}


void LIB_API Mesh::set_targetName(char mesh_targetName[FILENAME_MAX]){
    strcpy(targetName, mesh_targetName);
}

void LIB_API Mesh::render(){
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
