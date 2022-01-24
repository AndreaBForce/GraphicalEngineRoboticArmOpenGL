#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Engine.h"
#include "Node.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "Test.h"

///////////////////////
// GLOBAL VARIABLES //
/////////////////////
int windowId;
Engine* engine;
int fps = 0;
int frames = 0;
bool cameraPosition = true;

//GLOBAL ARM ANGLES
float asse00 = 0.0f;


//GLOBAL FORK SETINGS
int maxForkClose = 17;
int actualFork = 0;
int maxBallClose = 5;
bool ballGrabbed = false;
glm::mat4 oldBall;
int ballTransfo;

//camera params
glm::vec3 eye(0.0f, 10.0f, 0.0f);
glm::vec3 up(0.0f, 1.0f, 0.0f);
glm::vec3 center(0.0f, 0.0f, 40.0f);

Camera* cam1 = new Camera(glm::vec3(-40.0f, 50.0f, -65.0f), glm::vec3(40.0f, 0.0f, 40.0f), up);
Camera* cam2 = new Camera(eye, center, up);
Camera* mainCam;

//Global for controls
bool wireframe = true;
bool tooltip = true;

/////////////////////////
// CALLBACK FUNCTIONS //
///////////////////////

void displayCallback(){
    engine->clearDisplay();

    //questo metodo per renderizzare tutto una volta implementato correttamente
    engine->getRenderList()->renderList(mainCam->getCameraMat());

    
    char texts[64];
    sprintf(texts, "FPS: %d", fps);
    engine->write2DText(texts,1.0f,engine->getHeight()-14);

    if (tooltip) {
        strcpy(texts, "------------------------------");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 2));
        strcpy(texts, "Comandi Braccio");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 3));

        strcpy(texts, "[y] Rotate Base CCW");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 4));
        strcpy(texts, "[x] Rotate Base CW");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 5));

        strcpy(texts, "[d] Rotate Asse 00 UP");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 6));
        strcpy(texts, "[c] Rotate Asse 00 DOWN");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 7));

        strcpy(texts, "[f] Rotate Asse 01 UP");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 8));
        strcpy(texts, "[v] Rotate Asse 01 DOWN");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 9));

        strcpy(texts, "[g] Rotate Asse 02 UP");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 10));
        strcpy(texts, "[b] Rotate Asse 02 DOWN");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 11));

        strcpy(texts, "[h] Rotate Asse Force UP");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 12));
        strcpy(texts, "[n] Rotate Asse Forca DOWN");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 13));

        strcpy(texts, "[j] Apri forche");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 14));
        strcpy(texts, "[k] Stringi forche");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 15));


        strcpy(texts, "------------------------------");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 16));
        strcpy(texts, "Utilities");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 17));
        strcpy(texts, "[q] Resetta scena");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 18));
        strcpy(texts, "[z] Enable/Disable wireframe");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 19));
        strcpy(texts, "[u] Enable/Disable tooltip");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 20));


        strcpy(texts, "------------------------------");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 21));
        strcpy(texts, "Camera controls");
        engine->write2DText(texts, 1.0f, engine->getHeight() - (14 * 22));

    }


    frames++;

    engine->swapBuffer();
    engine->forceRendering(windowId);
}

void specialCallback(int key, int mouseX, int mouseY){

    float speed = 1.0f;

    switch(key){
        case KEY_UP:
            std::cout << "KEY UP" << std::endl;
            if(cameraPosition)
                eye.y += speed;
            else
                center.y += speed;
            break;
        case KEY_DOWN:
            std::cout << "KEY DOWN" << std::endl;
            if(cameraPosition)
                eye.y -= speed;
            else
                center.y -= speed;
            break;
        case KEY_LEFT:
            std::cout << "KEY LEFT" << std::endl;
            if(cameraPosition)
                eye.z -= speed;
            else
                center.z -= speed;
            break;
        case KEY_RIGHT:
            std::cout << "KEY RIGHT" << std::endl;
            if(cameraPosition)
                eye.z += speed;
            else
                center.z += speed;
            break;
    }

    cam2->setEye(eye);
    cam2->setCenter(center);

   engine->forceRendering(windowId);
}

bool check_distance_two_vectors(Node* node1,Node* node2,float range) {

    //L'ultima colonna delle final matrix contiene i vettori in world cordinates cosi possiamo confrontarli

    glm::vec4 node1WorldCoordinate = glm::column(node1->getFinalMatrix(), 3);
    glm::vec4 node2WorldCoordinate = glm::column(node2->getFinalMatrix(), 3);

    std::cout << node1WorldCoordinate.r << std::endl;
    std::cout << node1WorldCoordinate.g << std::endl;
    std::cout << node1WorldCoordinate.b << std::endl;

    std::cout << node2WorldCoordinate.r << std::endl;
    std::cout << node2WorldCoordinate.g << std::endl;
    std::cout << node2WorldCoordinate.b << std::endl;

    std::cout << glm::distance(node1WorldCoordinate, node2WorldCoordinate) << std::endl;
    if (glm::distance(node1WorldCoordinate, node2WorldCoordinate) <= range) {
        return true;
    }
    else {
        return false;
    }
}

void keyboardCallback(unsigned char key, int mouseX, int mouseY){

    float speed = 1.0f;
    float translate_factor_fork = 0.05f;


    Node* ballObjectToBeTaken;
    Node* rotateAxisForkFather;
    Node* rotateAxisBase;

    glm::vec3 rotateAxisX(1.0f, 0.0f, 0.0f);
    glm::vec3 rotateAxisY(0.0f, 1.0f, 0.0f);
    glm::vec3 rotateAxisZ(0.0f, 0.0f, 1.0f);

    glm::vec3 translateFork(0.0f, 0.0f, translateFactorFork);
    glm::vec3 translateNulla(0.0f, 0.0f, 0.0f);

    glm::vec3 translateBall(-3.5f, 1.5f, 2.6f);

    glm::vec3 translateBallFloor(0.0f,0.25f,0.0f);

    glm::vec3 scaleBall(1.20f, 1.0f, 1.0f);

    switch(key){
        case 'e':
            if(cameraPosition)
                eye.x += speed;
            else
                center.x += speed;
            break;
        case 'r':
            if(cameraPosition)
                eye.x -= speed;
            else
                center.x -= speed;
            break;
        case 'p':
            cameraPosition = !cameraPosition;
            break;
        case '1':
            //switch to cam1
            std::cout << "P PRESSED" << std::endl;
            mainCam = cam1;
            break;
        case '2':
            //switch to cam2
            std::cout << "O PRESSED" << std::endl;
            mainCam = cam2;
            break;

        case 'y':
            //CCW
            //Ruota base free
            std::cout << "Y PRESSED" << std::endl;
            engine->rotateNode("RotateBase", 0.5f, rotateAxisY);
            break;

        case 'x':
            //CW
            //Ruota base free
            std::cout << "X PRESSED" << std::endl;
            engine->rotateNode("RotateBase", -0.5f, rotateAxisY);
            break;

        case 'd':
            //Up
            std::cout << "D PRESSED" << std::endl;

            engine->rotateNode("RuotaAsse00", 0.5, rotateAxisZ);
            break;

        case 'c':
            //Down
            std::cout << "C PRESSED" << std::endl;
            engine->rotateNode("RuotaAsse00", -0.5, rotateAxisZ);
            break;
        case 'f':
            //Up
            std::cout << "F PRESSED" << std::endl;
            engine->rotateNode("RuotaAsse01", 0.5f, rotateAxisZ);
            break;

        case 'v':
            //Down
            std::cout << "V PRESSED" << std::endl;
            engine->rotateNode("RuotaAsse01", -0.5f, rotateAxisZ);
            break;
        case 'g':
            //Up
            std::cout << "G PRESSED" << std::endl;
            engine->rotateNode("RuotaAsse02", 0.5f, rotateAxisZ);
            break;

        case 'b':
            //Down
            std::cout << "B PRESSED" << std::endl;
            engine->rotateNode("RuotaAsse02", -0.5f, rotateAxisZ);
            break;
        case 'h':
            //Up
            std::cout << "H PRESSED" << std::endl;

            engine->rotateNode("RuotaAsseForca", 0.5f, rotateAxisZ);
            std::cout << glm::to_string((dynamic_cast<Node*>(engine->getRenderList()->getElementByName("RuotaAsseForca"))->getFinalMatrix())) << std::endl;
            break;

        case 'n':
            //Down
            std::cout << "N PRESSED" << std::endl;
            engine->rotateNode("RuotaAsseForca", -0.5f, rotateAxisZ);
            std::cout << glm::to_string((dynamic_cast<Node*>(engine->getRenderList()->getElementByName("RuotaAsseForca"))->getFinalMatrix())) << std::endl;
            break;
        case 'j':
            //apri pinza
            //Per capire meglio parti dal caso K che spiega la parte di chiusura, poi guardare l'apertura
            std::cout << "J PRESSED" << std::endl;

            //If che se ho le forche che sono maggiori di 0 significa che sono parzialmente chiuse quindi entro qua
            if (actualFork >= 0) {

                //Questo if serve per la parte di scalare la palla quando apro le forche
                if (ballGrabbed) {
                    //Prendo il nodo palla, metto la vecchia matrice di posizione ovvero quella originale senza transformazioni
                    ballObjectToBeTaken = (dynamic_cast<Node*>(engine->getRenderList()->getElementByName("Sphere001")));
                    ballObjectToBeTaken->setPosMatrix(oldBall);

                    //Qua applico la transformazione n-1 volte di quanto erano state applicate prima
                    for (int i = 0; i < actualFork; i++) {
                        engine->scaleNode("Sphere001",scaleBall);
                    }
                    //ri renderizzo la scena
                    displayCallback();
                }


                //Questo if serve per quando rilascio la palla
                if (actualFork == 0 && ballGrabbed) {
                    //release ball

                    //Prendo il nodo palla
                    ballObjectToBeTaken = (dynamic_cast<Node*>(engine->getRenderList()->getElementByName("Sphere001")));



                    //Vado a leggere l'ultima colonna della matrice finale,Essa corrisponde alle world coordinates della palla.
                    glm::vec4 ball_world_coordinate = glm::column(ballObjectToBeTaken->getFinalMatrix(), 3);

                    //Qua mi salvo la matrice iniziale(ovvero presa sulla forca) in world coordinates
                    glm::mat4 matriceInzialeePalle = glm::translate(glm::mat4(1.0f), glm::vec3(ball_world_coordinate.r, ball_world_coordinate.g, ball_world_coordinate.b));
                    //Qua salvo la matrice finale della palla in world coordinates, ovvero con la y messa a 1
                    glm::mat4 matriceFinalePalle = glm::translate(glm::mat4(1.0f), glm::vec3(ball_world_coordinate.r, 1.0f, ball_world_coordinate.b));


                    //Setto il padre della palla il nodo root della scena, poi metto la sua pos matrix come la matrice in world coordinates che ha adesso
                    ballObjectToBeTaken->setParent(engine->getRoot());
                    ballObjectToBeTaken->setPosMatrix(matriceInzialeePalle);

                    //while che fa l'animazione di caduta della palla
                    //finche la componente y delle world coordinates della palla non � >=1 lui decrementa
                    while (ball_world_coordinate.g >= 1) {

                        //Aggiorno la matrice inziale della palla
                        matriceInzialeePalle = ballObjectToBeTaken->getPosMatrix();

                        //Effetuo la traslazione della palla
                        ballObjectToBeTaken->setPosMatrix(glm::translate(matriceInzialeePalle, -translateBallFloor));

                        //aggiorno il ball_world coordinates della palla
                        ball_world_coordinate = glm::column(ballObjectToBeTaken->getFinalMatrix(), 3);

                        //renderizzo la scena
                        displayCallback();

                    }


                    //Setto come matrice della palla quella finale dichiarata prima, perch� � piu precisa
                    ballObjectToBeTaken->setPosMatrix(matriceFinalePalle);

                    //resetto la flag
                    ballGrabbed = false;
                }

                //traslo le forche
                engine->translateNode("forca1", translateFork);
                engine->translateNode("forca2", -translateFork);
                //nego le pinze
                actualFork--;
            }
            break;

        case 'k':
            //chiud pinza
            std::cout << "K PRESSED" << std::endl;

            //Qui vado a prendere i nodi che mi servono ovvero la palla e il RuotaAsseForca, che usero come padre dopo
            ballObjectToBeTaken = (dynamic_cast<Node*>(engine->getRenderList()->getElementByName("Sphere001")));
            rotateAxisForkFather = (dynamic_cast<Node*>(engine->getRenderList()->getElementByName("RuotaAsseForca")));


            //Questo if, controlla se la forca abbia raggiunto la posizione massima di chiusura
            if (actualFork < maxForkClose) {

                //Questo if, controlla se la forca sia aperta del tutto e se la distanza tra la palla e il padre sia < 5.0
                if (actualFork == 0 && check_distance_two_vectors(ballObjectToBeTaken, rotateAxisForkFather, 5.0f)) {



                    //Qui vado a settare la matrice di posizione della palla, uguale a quella della ruota asse forca
                    ballObjectToBeTaken->setPosMatrix(rotateAxisForkFather->getPosMatrix());

                    //Poi vado a settare la ruota asse forca come padre
                    ballObjectToBeTaken->setParent(rotateAxisForkFather);

                    //Dopo di che effettuo una traslazione perche altrimenti sarebbe dentro il padre
                    engine->translateNode("Sphere001", translateBall);

                    //Salvo un save point di come era originalmente la palla che viene usato dopo nella parte di release della palla
                    oldBall = ballObjectToBeTaken->getPosMatrix();

                    //flaggo a true il fatto che ho la palla grabbata
                    ballGrabbed = true;
                }


                //If che controlla se palla presa, e le forche sono <=2, posso chiudere ancora
                if (ballGrabbed && actualFork <= 2) {
                    engine->scaleNode("Sphere001", scaleBall);
                    engine->translateNode("forca1", -translateFork);
                    engine->translateNode("forca2", translateFork);
                    actualFork++;
                }
                //Altrimenti controllo se ho o meno la palla e se non l'ho posso chiudere di piu le forche
                else if(!ballGrabbed) {
                    engine->translateNode("forca1", -translateFork);
                    engine->translateNode("forca2", translateFork);
                    actualFork++;
                }

            }

            break;
        case 'z':
            engine->enableWireframe(wireframe);
            wireframe = !wireframe;
            break;
        case 'u':
            tooltip = !tooltip;
            break;
        case 'q':
            std::cout << "Q PRESSED" << std::endl;
            ballGrabbed = false;
            engine->restoreMemento();
            break;

    }

    cam2->setEye(eye);
    cam2->setCenter(center);
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

    engine = Engine::GetInstance();

    windowId = engine->init3Dcontext("Mangrovie Robotic Arm Project", 600, 600, argc, argv);

    Test* test = new Test();
    test->testExec();

    engine->setTextureFilePath("../files/textures/");
    engine->loadFromFile("../files/stanza.OVO");
    engine->setShadowFlag("Plane");

    mainCam = cam1;

    engine->setDisplayCallback(displayCallback);
    engine->setReshapeCallback();
    engine->setSpecialCallback(specialCallback);
    engine->setKeyboardCallback(keyboardCallback);
    engine->setTimerCallback(timerCallback, 1000, 0);

    engine->enableLightSystem();

    engine->enableMemento();

    engine->startEventLoop();

    engine->freeContext();

    return 0;
}
