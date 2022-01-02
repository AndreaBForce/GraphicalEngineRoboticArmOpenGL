#include <iostream>
#include "Engine.h"
#include "Node.h"
#include "Mesh.h"

int main(int argc, char *argv[]){

    std::cout << "Sono il client" << std::endl;
    Engine* engine = Engine::GetInstance();

    engine->engineMsg();
    Node* root = new Node();
    Mesh* mesh = new Mesh();
    mesh->set_parent(root);
    //engine->loadTree(root);
    engine->init("Test iniziale fatto molto male", 100, 100, argc, argv);

    engine->loadFromFile("C:/Users/andre/Documents/3ds Max 2020/export/braccio.OVO");
    return 0;

    //VISUAL STUDIO PER APRIRLO,
    //APRI IL VECCHIO VCPROJ, POI FAI ADD DEI MODULI E NULLA
    //SE DA PROBLEMI METTI LIBAPI DAVANTI AL METODO CHE ERA QUELLO

}
