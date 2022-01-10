#include "Node.h"

Node::Node()
{
    //ctor
}

Node::~Node()
{
    //dtor
}

void Node::addChild(Node* childNode){
    this->children.push_back(childNode);
}
