#include <iostream>
#include "Engine.h"
#include "Node.h"
#include "Mesh.h"

int main(int argc, char *argv[]){

    std::cout << "Sono il client" << std::endl;
    Engine* engine = Engine::GetInstance();

    engine->engineMsg();
    Node* root;
    Mesh* mesh;
    mesh->set_parent(root);
    //engine->loadTree(root);
    engine->init("Test iniziale fatto molto male", 100, 100, argc, argv);
    return 0;
}
