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
Mesh* testMesh;
float lightPosX = 0.0f;
float lightPosY = 5.0f;
float lightPosZ = -30.0f;
int fps = 0;
int frames = 0;
glm::mat4 cameraMat;

//camera params
glm::vec3 eye(0.0f, 20.0f, 0.0f);
glm::vec3 up(0.0f, 1.0f, 0.0f);

/////////////////////////
// CALLBACK FUNCTIONS //
///////////////////////

void displayCallback(){
    //light->setPosition(glm::vec3(lightPosX, lightPosY, lightPosZ));
    cameraMat = glm::lookAt(eye, glm::vec3(lightPosX, lightPosY, lightPosZ), up);
    testL->setPosition(glm::vec3(lightPosX, lightPosY, lightPosZ));
    engine->clearDisplay();

    //questo metodo per renderizzare tutto una volta implementato correttamente
    engine->get_object_list()->render_list(cameraMat);

    char texts[64];
    sprintf(texts, "FPS: %d", fps);
    engine->write2DText(texts,1.0f,engine->get_height()-14);

   
    strcpy(texts,"[y] Rotate Base CCW");
    engine->write2DText(texts, 1.0f, engine->get_height() - (14*2));
    strcpy(texts,"[x] Rotate Base CW");
    engine->write2DText(texts, 1.0f, engine->get_height() - (14 * 3));

    strcpy(texts, "[d] Rotate Asse 00 UP");
    engine->write2DText(texts, 1.0f, engine->get_height() - (14 * 4));
    strcpy(texts, "[c] Rotate Asse 00 DOWN");
    engine->write2DText(texts, 1.0f, engine->get_height() - (14 * 5));

    strcpy(texts, "[f] Rotate Asse 01 UP");
    engine->write2DText(texts, 1.0f, engine->get_height() - (14 * 6));
    strcpy(texts, "[v] Rotate Asse 01 DOWN");
    engine->write2DText(texts, 1.0f, engine->get_height() - (14 * 7));

    strcpy(texts, "[g] Rotate Asse 02 UP");
    engine->write2DText(texts, 1.0f, engine->get_height() - (14 * 8));
    strcpy(texts, "[b] Rotate Asse 02 DOWN");
    engine->write2DText(texts, 1.0f, engine->get_height() - (14 * 9));

    strcpy(texts, "[h] Rotate Asse Force UP");
    engine->write2DText(texts, 1.0f, engine->get_height() - (14 * 10));
    strcpy(texts, "[n] Rotate Asse Forca DOWN");
    engine->write2DText(texts, 1.0f, engine->get_height() - (14 * 11));
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
    float forca = 2.0f;
    glm::vec3 rotateAxisX(1.0f, 0.0f, 0.0f);
    glm::vec3 rotateAxisY(0.0f, 1.0f, 0.0f);
    glm::vec3 rotateAxisZ(0.0f, 0.0f, 1.0f);
    glm::vec3 translate_forca(0.0f, forca, 0.0f);
    switch(key){
        case 'w':
            std::cout << "W PRESSED" << std::endl;
            lightPosY += speed;
            break;
        case 's':
            std::cout << "S PRESSED" << std::endl;
            lightPosY -= speed;
            break;

        case 'y':
            //CCW
            std::cout << "Y PRESSED" << std::endl;
            engine->rotate_node("RotateBase", 0.5f, rotateAxisY);
            break;

        case 'x':
            //CW
            std::cout << "X PRESSED" << std::endl;
            engine->rotate_node("RotateBase", -0.5f, rotateAxisY);
            break;

        case 'd':
            //Up
            std::cout << "D PRESSED" << std::endl;
            engine->rotate_node("RuotaAsse00", 0.5f, rotateAxisY);
            break;

        case 'c':
            //Down
            std::cout << "C PRESSED" << std::endl;
            engine->rotate_node("RuotaAsse00", -0.5f, rotateAxisY);
            break;
        case 'f':
            //Up
            std::cout << "F PRESSED" << std::endl;
            engine->rotate_node("RuotaAsse01", 0.5f, rotateAxisY);
            break;

        case 'v':
            //Down
            std::cout << "V PRESSED" << std::endl;
            engine->rotate_node("RuotaAsse01", -0.5f, rotateAxisY);
            break;
        case 'g':
            //Up
            std::cout << "G PRESSED" << std::endl;
            engine->rotate_node("RuotaAsse02", 0.5f, rotateAxisY);
            break;

        case 'b':
            //Down
            std::cout << "B PRESSED" << std::endl;
            engine->rotate_node("RuotaAsse02", -0.5f, rotateAxisY);
            break;
        case 'h':
            //Up
            std::cout << "H PRESSED" << std::endl;
            engine->rotate_node("RuotaAsseForca", 0.5f, rotateAxisY);
            break;

        case 'n':
            //Down
            std::cout << "N PRESSED" << std::endl;
            engine->rotate_node("RuotaAsseForca", -0.5f, rotateAxisY);
            break;
        case 'j':
            //apri pinza
            std::cout << "J PRESSED" << std::endl;
            
            engine->translate_node("forca1", translate_forca);
            engine->translate_node("forca2", -translate_forca);
               
            break;

        case 'k':
            //chiud pinza
            std::cout << "K PRESSED" << std::endl;
           
            

            engine->translate_node("forca1", -translate_forca);
            engine->translate_node("forca2", translate_forca);
               
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

    windowId = engine->init3Dcontext("Project", 600, 600, argc, argv);

    engine->setTextureFilePath("../files/");
    engine->loadFromFile("../files/room.ovo");

    for(int i = 0; i < engine->getRoot()->get_number_of_children(); i++){
        std::cout << engine->getRoot()->getChildren().at(i)->get_name() << std::endl;
    }

    testL = dynamic_cast<Light*>(engine->getRoot()->getChildren().at(5));
    //testMesh = dynamic_cast<Mesh*>(engine->getRoot()->getChildren().at(0));
    testMesh = dynamic_cast<Mesh*>(engine->get_object_list()->get_list().at(16));

    //testMesh->render();

    //light->setPosition(glm::vec3(0.0f, -3.0f, -30.0f));
    light->setLightType(lightType::OMNI);
    light->setAmbient(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    light->setDiffuse(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    light->setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    light->setDirection(glm::vec3(0.0f, 0.0f, 0.0f));
    light->setCutoff(180.0f);


    engine->setDisplayCallback(displayCallback);
    engine->setReshapeCallback();
    engine->setSpecialCallback(specialCallback);
    engine->setKeyboardCallback(keyboardCallback);
    engine->setTimerCallback(timerCallback, 1000, 0);


    engine->enableLightSystem();

    engine->startEventLoop();

    engine->endEventLoop();

    return 0;

    //VISUAL STUDIO PER APRIRLO,
    //APRI IL VECCHIO VCPROJ, POI FAI ADD DEI MODULI E NULLA
    //SE DA PROBLEMI METTI LIBAPI DAVANTI AL METODO CHE ERA QUELLO

}
