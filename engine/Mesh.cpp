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

    glLoadMatrixf(glm::value_ptr(camera * this->get_final_matrix()));

    glEnable(GL_NORMALIZE);

    if(material->hasTexture())
        glEnable(GL_TEXTURE_2D);

    for(unsigned int* face : faces){
        //std::cout << "   Face data . . :  f" << " (" << face[0] << ", " << face[1] << ", " << face[2] << ")" << std::endl;
        glBegin(GL_TRIANGLES);

            glNormal3fv(glm::value_ptr(vertices.at(face[0])->getNormal()));
            glTexCoord2fv(glm::value_ptr(vertices.at(face[0])->getUv()));
            glVertex3fv(glm::value_ptr(vertices.at(face[0])->getVertex()));

            glNormal3fv(glm::value_ptr(vertices.at(face[1])->getNormal()));
            glTexCoord2fv(glm::value_ptr(vertices.at(face[1])->getUv()));
            glVertex3fv(glm::value_ptr(vertices.at(face[1])->getVertex()));

            glNormal3fv(glm::value_ptr(vertices.at(face[2])->getNormal()));
            glTexCoord2fv(glm::value_ptr(vertices.at(face[2])->getUv()));
            glVertex3fv(glm::value_ptr(vertices.at(face[2])->getVertex()));

        glEnd();
    }

    if(material->hasTexture())
        glDisable(GL_TEXTURE_2D);
}
