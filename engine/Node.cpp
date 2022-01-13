#include "Node.h"
#include <iostream>

LIB_API Node::Node()
{
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
