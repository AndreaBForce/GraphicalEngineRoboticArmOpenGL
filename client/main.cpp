#include <iostream>
#include "Engine.h"

int main(int argc, char *argv[]){

    std::cout << "Sono il client" << std::endl;
    Engine* engine = Engine::GetInstance();

    engine->engineMsg();
    engine->loadFromFile("C:/Users/andre/Documents/3ds Max 2020/export/braccio.OVO");
    //engine->init("Test iniziale fatto molto male", 640, 640, argc,argv);
    return 0;


    //VISUAL STUDIO PER APRIRLO,
    //APRI IL VECCHIO VCPROJ, POI FAI ADD DEI MODULI E NULLA
    //SE DA PROBLEMI METTI LIBAPI DAVANTI AL METODO CHE ERA QUELLO

}
