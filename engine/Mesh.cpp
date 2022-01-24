#include "Mesh.h"
#include "Utils.h"
#include "Engine.h"
#include <iostream>
#include <GL/freeglut.h>

LIB_API Mesh::Mesh()
{
    hasShadow = false;
    //ctor
}

LIB_API Mesh::~Mesh()
{
    std::cout << "Mesh " << this->get_name() << std::endl;
    //dtor
}

LIB_API Material* Mesh::get_material(){
    return materialPtr.get();
}

void LIB_API Mesh::setChildren(unsigned int mesh_children){
    children = mesh_children;
}


void LIB_API Mesh::render(glm::mat4 camera){

    // render material
    materialPtr->render(camera);

    glLoadMatrixf(glm::value_ptr(camera * this->getFinalMatrix()));

    glEnable(GL_NORMALIZE);

    if(materialPtr->hasTexture())
        glEnable(GL_TEXTURE_2D);

    for(unsigned int* face : faces){
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

    if(materialPtr->hasTexture())
        glDisable(GL_TEXTURE_2D);

    if (hasShadow)
        renderShadow(camera);
}

void LIB_API Mesh::renderShadow(glm::mat4 camera){

    glm::mat4 scaleShadow = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 1.0f));
    glm::mat4 transShadow = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.001f, 0.0f));
    glm::mat4 shadowMat = Engine::GetInstance()->getShadowMatrix();

    //render material
    Engine::GetInstance()->getShadowMaterial()->render(camera);

    glLoadMatrixf(glm::value_ptr(camera * shadowMat * this->getFinalMatrix()));

    for(unsigned int* face : faces){
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
}
