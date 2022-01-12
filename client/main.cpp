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
Light* testL;
float lightPosX = 0.0f;
float lightPosY = -3.0f;
float lightPosZ = -30.0f;
int fps = 0;
int frames = 0;

/////////////////////////
// CALLBACK FUNCTIONS //
///////////////////////

void displayCallback(){
    std::cout << "callback lato client" << std::endl;
    //light->setPosition(glm::vec3(lightPosX, lightPosY, lightPosZ));
    testL->setPosition(glm::vec3(lightPosX, lightPosY, lightPosZ));
    engine->clearDisplay();


    //light->render();
    testL->render();
    cube->render();


    char texts[64];
    sprintf(texts, "FPS: %d", fps);
    engine->write2DText(texts,1.0f,14.0f);

    frames++;


    engine->swapBuffer();
    engine->forceRendering(windowId);
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

void timerCallback(int value) {
    fps = frames;
    frames = 0;
    engine->setTimerCallback(timerCallback,1000, 0);
}

///////////
// MAIN //
/////////

int main(int argc, char *argv[]){

    std::cout << "Sono il client" << std::endl;
    engine = Engine::GetInstance();

    engine->engineMsg();
    engine->loadFromFile("../files/room.ovo");

    for(int i = 0; i < engine->getRoot()->get_number_of_children(); i++){
        std::cout << engine->getRoot()->getChildren().at(i)->get_name() << std::endl;
    }

    testL = dynamic_cast<Light*>(engine->getRoot()->getChildren().at(5));

    //light->setPosition(glm::vec3(0.0f, -3.0f, -30.0f));
    light->setLightType(lightType::OMNI);
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
    engine->setTimerCallback(timerCallback, 1000, 0);


    engine->enableLightSystem();

    engine->startEventLoop();

    //engine->endEventLoop();

    return 0;

    //VISUAL STUDIO PER APRIRLO,
    //APRI IL VECCHIO VCPROJ, POI FAI ADD DEI MODULI E NULLA
    //SE DA PROBLEMI METTI LIBAPI DAVANTI AL METODO CHE ERA QUELLO

}
