#ifndef NODE_H
#define NODE_H
#include "Object.h"
#include <vector>


class Node : public Object
{
    public:
        Node();
        virtual ~Node();
        virtual void render();

        glm::mat4 get_pos_matrix(){return pos_matrix;}
        Node* get_parent(){return parent;}
        int get_number_of_children(){return children.size();}
        Node get_node_by_name();
        glm::mat4 get_final_matrix();

        void tree_traversal();
        void set_parent(Node *new_parent){parent = new_parent;}

    private:
        glm::mat4 pos_matrix;
        Node* parent;
        std::vector<Node> children;
};

#endif // NODE_H