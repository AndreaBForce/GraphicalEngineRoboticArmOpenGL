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


void LIB_API Mesh::render(glm::mat4 camera){
    //std::cout << "render mesh -> " << this->get_name() << std::endl;

    // Set material properties:
    material->render(camera);
    //glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0f);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)));
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)));
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

    //std::cout << "Nr faces: " << this->faces.size() << std::endl;
    //std::cout << "Nr vertices: " << this->vertices.size() << std::endl;


    //for(Vertex* vert : vertices){
    //    glm::vec3 firstVertex = vert->getVertex();
    //    std::cout << "Vertex: " << " (" << firstVertex.x << ", " << firstVertex.y << ", " << firstVertex.z << ")" << std::endl;
    //}

    //unsigned int* ptr = this->faces.front();
    //std::cout << "   Face data . . :  f" << " (" << ptr[0] << ", " << ptr[1] << ", " << ptr[2] << ")" << std::endl;

    //glm::mat4 transCube = glm::translate(glm::mat4(1.0f), glm::vec3(-20.0f, 0.0f, -60.0f));
    //glLoadMatrixf(glm::value_ptr(transCube));

    glLoadMatrixf(glm::value_ptr(camera * this->get_final_matrix()));


    glEnable(GL_NORMALIZE);

    for(unsigned int* face : faces){
        //std::cout << "   Face data . . :  f" << " (" << face[0] << ", " << face[1] << ", " << face[2] << ")" << std::endl;
        glBegin(GL_TRIANGLES);

            glNormal3fv(glm::value_ptr(vertices.at(face[0])->getNormal()));
            glVertex3fv(glm::value_ptr(vertices.at(face[0])->getVertex()));

            glNormal3fv(glm::value_ptr(vertices.at(face[1])->getNormal()));
            glVertex3fv(glm::value_ptr(vertices.at(face[1])->getVertex()));

            glNormal3fv(glm::value_ptr(vertices.at(face[2])->getNormal()));
            glVertex3fv(glm::value_ptr(vertices.at(face[2])->getVertex()));

        glEnd();
    }

    // Position and render the cube:
    //glm::mat4 transCube = glm::translate(glm::mat4(1.0f), glm::vec3(-20.0f, 0.0f, -60.0f));
    //glLoadMatrixf(glm::value_ptr(transCube));
    //glutSolidCube(10.0f);
}
