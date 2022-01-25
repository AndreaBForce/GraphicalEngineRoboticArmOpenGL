#ifndef NODE_H
#define NODE_H
#include "Object.h"
#include "Utils.h"
#include <vector>

class LIB_API Node : public Object
{
    public:
        Node();
        virtual ~Node();
        void render(glm::mat4 camera) {};

        glm::mat4 getPosMatrix(){return posMatrix;}
        Node* getParent(){return parent;}
        int getNumberOfChildren(){return children.size();}

        glm::mat4 getFinalMatrix();

        std::vector<Node*> getChildren(){return children;};

        void setParent(Node* newParent){parent = newParent;};
        void addChild(Node* childNode);
        void setPosMatrix(glm::mat4 newPosMatrix){posMatrix = newPosMatrix;};

        void restoreMemento();
        void setMemento();

    private:
        glm::mat4 posMatrix;
        glm::mat4 memento;
        Node* mementoParent;

        Node* parent;
        std::vector<Node*> children;
};

#endif // NODE_H
