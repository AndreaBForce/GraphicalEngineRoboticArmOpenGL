#include <iostream>
#include "Engine.h"
#include "Node.h"
#include "Mesh.h"
#include "Light.h"

///////////////////////
// GLOBAL VARIABLES //
/////////////////////
int windowId;
Engine* engine;
Mesh* cube = new Mesh();
Light* light = new Light();
float lightPosX = 0.0f;
float lightPosY = -3.0f;
float lightPosZ = -30.0f;

/////////////////////////
// CALLBACK FUNCTIONS //
///////////////////////

void displayCallback(){
    std::cout << "callback lato client" << std::endl;
    light->setPosition(glm::vec3(lightPosX, lightPosY, lightPosZ));
    engine->clearDisplay();


    light->render();
    cube->render();

    engine->swapBuffer();
}

void specialCallback(int key, int mouseX, int mouseY){

    float speed = 0.5f;

    switch(key){
        case KEY_UP:
            std::cout << "KEY UP" << std::endl;
            lightPosZ -= speed;
            break;
        case KEY_DOWN:
            std::cout << "KEY DOWN" << std::endl;
            lightPosZ += speed;
            break;
        case KEY_LEFT:
            std::cout << "KEY LEFT" << std::endl;
            lightPosX -= speed;
            break;
        case KEY_RIGHT:
            std::cout << "KEY RIGHT" << std::endl;
            lightPosX += speed;
            break;
    }

    engine->forceRendering(windowId);
}

void keyboardCallback(unsigned char key, int mouseX, int mouseY){

    float speed = 0.5f;
    switch(key){
        case 'w':
            std::cout << "W PRESSED" << std::endl;
            lightPosY += speed;
            break;
        case 's':
            std::cout << "S PRESSED" << std::endl;
            lightPosY -= speed;
            break;
    }

    engine->forceRendering(windowId);
}

///////////
// MAIN //
/////////

int main(int argc, char *argv[]){

    std::cout << "Sono il client" << std::endl;
    engine = Engine::GetInstance();

    engine->engineMsg();
    Node* root = new Node();
    Mesh* mesh = new Mesh();
    mesh->set_parent(root);
    //engine->loadTree(root);

    //light->setPosition(glm::vec3(0.0f, -3.0f, -30.0f));
    light->setAmbient(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    light->setDiffuse(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    light->setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    light->setDirection(glm::vec3(0.0f, 0.0f, 0.0f));
    light->setCutoff(180.0f);

    windowId = engine->init3Dcontext("Project", 600, 600, argc, argv);

    engine->setDisplayCallback(displayCallback);
    engine->setReshapeCallback();
    engine->setSpecialCallback(specialCallback);
    engine->setKeyboardCallback(keyboardCallback);

    engine->enableLightSystem();

    engine->startEventLoop();

    //engine->endEventLoop();

    //engine->loadFromFile("C:/Users/andre/Documents/3ds Max 2020/export/braccio.OVO");
    return 0;

    //VISUAL STUDIO PER APRIRLO,
    //APRI IL VECCHIO VCPROJ, POI FAI ADD DEI MODULI E NULLA
    //SE DA PROBLEMI METTI LIBAPI DAVANTI AL METODO CHE ERA QUELLO

}
