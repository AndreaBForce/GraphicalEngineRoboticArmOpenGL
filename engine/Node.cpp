#include "Node.h"
#include <iostream>
#include <glm/gtx/matrix_decompose.hpp>
LIB_API Node::Node()
{
    this->pos_matrix = glm::mat4(1.0f);
    //ctor
}

LIB_API Node::~Node()
{
    //dtor
}

void LIB_API Node::addChild(Node* childNode){
    this->children.push_back(childNode);
}


glm::mat4 LIB_API Node::get_final_matrix(){

    Node* cur = this;
    glm::mat4 finalMat(1.0f);

    while(cur->get_parent() != nullptr){

        finalMat = cur->get_pos_matrix() * finalMat;

        cur = cur->get_parent();
    }

    return finalMat;
}

void LIB_API Node::set_affine_decomposition(Node* nodo_affine) {
    glm::vec3 scale;
    glm::quat orientation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;

    glm::decompose(nodo_affine->get_pos_matrix(), scale, orientation, translation, skew, perspective);

    nodo_affine->set_scale(scale);
    nodo_affine->set_orientation(orientation);

}

//https://forum.openframeworks.cc/t/decomposing-glm-mat4-and-setting-transform-to-ofnode/29516
//decomposizione affine
//solo componenti vettore scaling trasformi in matrie
//invera matrice e molti per matrice pallina cosi annulli socio
//attacchi casot
