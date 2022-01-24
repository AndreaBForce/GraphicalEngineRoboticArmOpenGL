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
        Node getNodeByName();
        glm::mat4 getFinalMatrix();
        std::vector<Node*> getChildren(){return children;};
        glm::quat getOrientation() { return orientation; };

        void treeTraversal();
        void setParent(Node* newParent){parent = newParent;}
        void addChild(Node* childNode);
        void setPosMatrix(glm::mat4 newPosMatrix){posMatrix = newPosMatrix;}

        void setScale(glm::vec3 scala) { scale = scala; };
        void setOrientation(glm::quat orientation1) { orientation = orientation1; };
        void setTranslation(glm::vec3 translatio) { translation = translatio; };

        glm::vec3 getTranslation() { return translation; };
        glm::vec3 getScale() { return scale; };

    private:
        glm::mat4 posMatrix;
        Node* parent;
        std::vector<Node*> children;

        glm::vec3 scale;
        glm::quat orientation;
        glm::vec3 translation;
        glm::vec3 skew;
        glm::vec4 perspective;
};

#endif // NODE_H
