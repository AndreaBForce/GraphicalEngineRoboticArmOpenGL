#include <iostream>
#include "simpleClass.h"

int main(int argc, char *argv[]){

    std::cout << "Sono il client" << std::endl;
    simpleClass obj;
    obj.engineMsg();

    obj.init("Test iniziale fatto molto male", 640, 640, argc,argv);
    return 0;
}
