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

        glm::mat4 get_pos_matrix(){return pos_matrix;}
        Node* getParent(){return parent;}
        int getNumberOfChildren(){return children.size();}
        Node getNodeByName();
        glm::mat4 getFinalMatrix();
        std::vector<Node*> getChildren(){return children;};
        glm::quat getOrientation() { return orientation; };

        void tree_traversal();
        void set_parent(Node* new_parent){parent = new_parent;}
        void addChild(Node* childNode);
        void set_pos_matrix(glm::mat4 new_pos_matrix){pos_matrix = new_pos_matrix;}

        void set_affine_decomposition(Node* nodo_affine);

        void set_scale(glm::vec3 scala) { scale = scala; };
        void set_orientation(glm::quat orientation1) { orientation = orientation1; };

        void set_translation(glm::vec3 translatio) { translation = translatio; };

        glm::vec3 get_translation() { return translation; };
        glm::vec3 get_scale() { return scale; };

    private:

        glm::mat4 pos_matrix;
        Node* parent;
        std::vector<Node*> children;

        glm::vec3 scale;
        glm::quat orientation;
        glm::vec3 translation;
        glm::vec3 skew;
        glm::vec4 perspective;
};

#endif // NODE_H
