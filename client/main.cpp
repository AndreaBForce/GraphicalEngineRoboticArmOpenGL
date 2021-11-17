#include <iostream>
#include "Engine.h"

int main(int argc, char *argv[]){

    std::cout << "Sono il client" << std::endl;
    Engine* engine = Engine::GetInstance();

    engine->engineMsg();
    engine->init("Test iniziale fatto molto male", 640, 640, argc,argv);
    return 0;
}
