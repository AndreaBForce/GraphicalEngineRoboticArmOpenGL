#include "Node.h"

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
