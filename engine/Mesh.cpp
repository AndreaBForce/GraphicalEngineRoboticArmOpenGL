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

Material* Mesh::get_material(){
    return material;
}

void Mesh::set_matrix(glm::mat4 mesh_matrix){
    matrix = mesh_matrix;
}

void Mesh::set_bBoxMin(glm::vec3 mesh_bBoxMin){
    bBoxMin = mesh_bBoxMin;
}

void Mesh::set_bBoxMax(glm::vec3 mesh_bBoxMax){
    bBoxMax = mesh_bBoxMax;
}

void Mesh::set_radius(float mesh_radius){
    radius = mesh_radius;
}

void Mesh::set_children(unsigned int mesh_children){
    children = mesh_children;
}

void Mesh::set_subtype(char mesh_subtypeName[FILENAME_MAX]){
    strcpy(subtypeName, mesh_subtypeName);
}


void Mesh::set_targetName(char mesh_targetName[FILENAME_MAX]){
    strcpy(targetName, mesh_targetName);
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
