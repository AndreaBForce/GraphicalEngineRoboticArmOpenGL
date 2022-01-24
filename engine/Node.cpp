#include "Node.h"
#include <iostream>
#include <glm/gtx/matrix_decompose.hpp>

LIB_API Node::Node()
{
    this->posMatrix = glm::mat4(1.0f);
    //ctor
}

LIB_API Node::~Node()
{
    //dtor
}



void LIB_API Node::addChild(Node* childNode){
    this->children.push_back(childNode);
}


glm::mat4 LIB_API Node::getFinalMatrix(){

    Node* cur = this;
    glm::mat4 finalMat(1.0f);

    while(cur->getParent() != nullptr){

        finalMat = cur->getPosMatrix() * finalMat;

        cur = cur->getParent();
    }

    return finalMat;
}

void LIB_API Node::restoreMemento() {
    parent = mementoParent;
    posMatrix = memento;

}

void LIB_API Node::setMemento() {
    memento = posMatrix;
    mementoParent = parent;
}