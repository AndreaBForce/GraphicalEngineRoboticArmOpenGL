#include <iostream>
#include "simpleClass.h"

int main(int argc, char *argv[]){

    std::cout << "Sono il client" << std::endl;
    simpleClass obj;
    obj.engineMsg();

    return 0;
}
