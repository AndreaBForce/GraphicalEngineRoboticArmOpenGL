#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/string_cast.hpp>


#include "Engine.h"
#include "Node.h"
#include "Mesh.h"
#include "Light.h"
#include "Test.h"

///////////////////////
// GLOBAL VARIABLES //
/////////////////////
int windowId;
Engine* engine;
float cameraPosX = 0.0f;
float cameraPosY = 5.0f;
float cameraPosZ = 30.0f;
int fps = 0;
int frames = 0;

//GLOBAL ARM ANGLES
float asse00 = 0.0f;


//GLOBAL FORK SETINGS
int max_fork_close = 17;
int actual_fork = 0;
int max_ball_close = 5;
bool ball_grabbed = false;
glm::mat4 old_ball;
int ball_transfo;


glm::mat4 cameraMat;

//camera params
glm::vec3 eye(-40.0f, 60.0f, 65.0f);
glm::vec3 up(0.0f, 1.0f, 0.0f);


/////////////////////////
// CALLBACK FUNCTIONS //
///////////////////////

void displayCallback(){
    cameraMat = glm::lookAt(eye, glm::vec3(cameraPosX, cameraPosY, cameraPosZ), up);
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

    strcpy(texts, "[j] Apri forche");
    engine->write2DText(texts, 1.0f, engine->get_height() - (14 * 12));
    strcpy(texts, "[k] Stringi forche");
    engine->write2DText(texts, 1.0f, engine->get_height() - (14 * 13));
    frames++;

    engine->swapBuffer();
    engine->forceRendering(windowId);
}

void specialCallback(int key, int mouseX, int mouseY){

    float speed = 0.5f;

    switch(key){
        case KEY_UP:
            std::cout << "KEY UP" << std::endl;
            cameraPosZ -= speed;
            break;
        case KEY_DOWN:
            std::cout << "KEY DOWN" << std::endl;
            cameraPosZ += speed;
            break;
        case KEY_LEFT:
            std::cout << "KEY LEFT" << std::endl;
            cameraPosX -= speed;
            break;
        case KEY_RIGHT:
            std::cout << "KEY RIGHT" << std::endl;
            cameraPosX += speed;
            break;
    }

   engine->forceRendering(windowId);
}

bool check_distance_two_vectors(Node* node1,Node* node2,float range) {
    
    //L'ultima colonna delle final matrix contiene i vettori in world cordinates cosi possiamo confrontarli

    glm::vec4 node1_world_coordinate = glm::column(node1->getFinalMatrix(), 3);
    glm::vec4 node2_world_coordinate = glm::column(node2->getFinalMatrix(), 3);

    std::cout << node1_world_coordinate.r << std::endl;
    std::cout << node1_world_coordinate.g << std::endl;
    std::cout << node1_world_coordinate.b << std::endl;

    std::cout << node2_world_coordinate.r << std::endl;
    std::cout << node2_world_coordinate.g << std::endl;
    std::cout << node2_world_coordinate.b << std::endl;

    std::cout << glm::distance(node1_world_coordinate, node2_world_coordinate) << std::endl;
    if (glm::distance(node1_world_coordinate, node2_world_coordinate) <= range) {
        return true;
    }
    else {
        return false;
    }
}

void keyboardCallback(unsigned char key, int mouseX, int mouseY){

    float speed = 0.5f;
    float translate_factor_fork = 0.05f;


    Node* ball_object_to_be_taken;
    Node* rotate_axis_fork_father;
    Node* rotate_axis_base;

    glm::vec3 rotateAxisX(1.0f, 0.0f, 0.0f);
    glm::vec3 rotateAxisY(0.0f, 1.0f, 0.0f);
    glm::vec3 rotateAxisZ(0.0f, 0.0f, 1.0f);

    glm::vec3 translate_fork(0.0f, 0.0f, translate_factor_fork);
    glm::vec3 translate_nulla(0.0f, 0.0f, 0.0f);

    glm::vec3 translate_ball(-3.5f, 1.5f, 2.6f);
    
    glm::vec3 translate_ball_floor(0.0f,0.25f,0.0f);

    glm::vec3 scale_ball(1.20f, 1.0f, 1.0f);

    switch(key){
        case 'w':
            std::cout << "W PRESSED" << std::endl;
            cameraPosY += speed;
            break;
        case 's':
            std::cout << "S PRESSED" << std::endl;
            cameraPosY -= speed;
            break;

        case 'y':
            //CCW
            //Ruota base free
            std::cout << "Y PRESSED" << std::endl;
            engine->rotate_node("RotateBase", 0.5f, rotateAxisY);
            break;

        case 'x':
            //CW
            //Ruota base free
            std::cout << "X PRESSED" << std::endl;
            engine->rotate_node("RotateBase", -0.5f, rotateAxisY);
            break;

        case 'd':
            //Up
            std::cout << "D PRESSED" << std::endl;
           
            engine->rotate_node("RuotaAsse00", 0.5, rotateAxisZ);
            break;

        case 'c':
            //Down
            std::cout << "C PRESSED" << std::endl;
            engine->rotate_node("RuotaAsse00", -0.5, rotateAxisZ);
            break;
        case 'f':
            //Up
            std::cout << "F PRESSED" << std::endl;
            engine->rotate_node("RuotaAsse01", 0.5f, rotateAxisZ);
            break;

        case 'v':
            //Down
            std::cout << "V PRESSED" << std::endl;
            engine->rotate_node("RuotaAsse01", -0.5f, rotateAxisZ);
            break;
        case 'g':
            //Up
            std::cout << "G PRESSED" << std::endl;
            engine->rotate_node("RuotaAsse02", 0.5f, rotateAxisZ);
            break;

        case 'b':
            //Down
            std::cout << "B PRESSED" << std::endl;
            engine->rotate_node("RuotaAsse02", -0.5f, rotateAxisZ);
            break;
        case 'h':
            //Up
            std::cout << "H PRESSED" << std::endl;
            
            engine->rotate_node("RuotaAsseForca", 0.5f, rotateAxisZ);
            std::cout << glm::to_string((dynamic_cast<Node*>(engine->get_object_list()->get_element_by_name("RuotaAsseForca"))->getFinalMatrix())) << std::endl;
            break;

        case 'n':
            //Down
            std::cout << "N PRESSED" << std::endl;
            engine->rotate_node("RuotaAsseForca", -0.5f, rotateAxisZ);
            std::cout << glm::to_string((dynamic_cast<Node*>(engine->get_object_list()->get_element_by_name("RuotaAsseForca"))->getFinalMatrix())) << std::endl;
            break;
        case 'j':
            //apri pinza
            //Per capire meglio parti dal caso K che spiega la parte di chiusura, poi guardare l'apertura
            std::cout << "J PRESSED" << std::endl;

            //If che se ho le forche che sono maggiori di 0 significa che sono parzialmente chiuse quindi entro qua
            if (actual_fork >= 0) {

                //Questo if serve per la parte di scalare la palla quando apro le forche
                if (ball_grabbed) {
                    //Prendo il nodo palla, metto la vecchia matrice di posizione ovvero quella originale senza transformazioni
                    ball_object_to_be_taken = (dynamic_cast<Node*>(engine->get_object_list()->get_element_by_name("Sphere001")));
                    ball_object_to_be_taken->set_pos_matrix(old_ball);

                    //Qua applico la transformazione n-1 volte di quanto erano state applicate prima
                    for (int i = 0; i < actual_fork; i++) {    
                        engine->scale_node("Sphere001",scale_ball);
                    }
                    //ri renderizzo la scena
                    displayCallback();
                }


                //Questo if serve per quando rilascio la palla
                if (actual_fork == 0 && ball_grabbed) {
                    //release ball
                    
                    //Prendo il nodo palla
                    ball_object_to_be_taken = (dynamic_cast<Node*>(engine->get_object_list()->get_element_by_name("Sphere001")));
                    
                   
                    
                    //Vado a leggere l'ultima colonna della matrice finale,Essa corrisponde alle world coordinates della palla.
                    glm::vec4 ball_world_coordinate = glm::column(ball_object_to_be_taken->getFinalMatrix(), 3);
                    
                    //Qua mi salvo la matrice iniziale(ovvero presa sulla forca) in world coordinates
                    glm::mat4 matriceInzialeePalle = glm::translate(glm::mat4(1.0f), glm::vec3(ball_world_coordinate.r, ball_world_coordinate.g, ball_world_coordinate.b));
                    //Qua salvo la matrice finale della palla in world coordinates, ovvero con la y messa a 1
                    glm::mat4 matriceFinalePalle = glm::translate(glm::mat4(1.0f), glm::vec3(ball_world_coordinate.r, 1.0f, ball_world_coordinate.b));
                   
                    
                    //Setto il padre della palla il nodo root della scena, poi metto la sua pos matrix come la matrice in world coordinates che ha adesso
                    ball_object_to_be_taken->set_parent(engine->getRoot());
                    ball_object_to_be_taken->set_pos_matrix(matriceInzialeePalle);

                    //while che fa l'animazione di caduta della palla
                    //finche la componente y delle world coordinates della palla non è >=1 lui decrementa
                    while (ball_world_coordinate.g >= 1) {
                   
                        //Aggiorno la matrice inziale della palla
                        matriceInzialeePalle = ball_object_to_be_taken->get_pos_matrix();
                      
                        //Effetuo la traslazione della palla
                        ball_object_to_be_taken->set_pos_matrix(glm::translate(matriceInzialeePalle, -translate_ball_floor));

                        //aggiorno il ball_world coordinates della palla
                        ball_world_coordinate = glm::column(ball_object_to_be_taken->getFinalMatrix(), 3);

                        //renderizzo la scena
                        displayCallback();
                       
                    }
                    
                    
                    //Setto come matrice della palla quella finale dichiarata prima, perchè è piu precisa
                    ball_object_to_be_taken->set_pos_matrix(matriceFinalePalle);
                   
                    //resetto la flag
                    ball_grabbed = false;
                }

                //traslo le forche
                engine->translate_node("forca1", translate_fork);
                engine->translate_node("forca2", -translate_fork);
                //nego le pinze
                actual_fork--;
            }
            break;

        case 'k':
            //chiud pinza
            std::cout << "K PRESSED" << std::endl;

            //Qui vado a prendere i nodi che mi servono ovvero la palla e il RuotaAsseForca, che usero come padre dopo
            ball_object_to_be_taken = (dynamic_cast<Node*>(engine->get_object_list()->get_element_by_name("Sphere001")));
            rotate_axis_fork_father = (dynamic_cast<Node*>(engine->get_object_list()->get_element_by_name("RuotaAsseForca")));
            

            //Questo if, controlla se la forca abbia raggiunto la posizione massima di chiusura
            if (actual_fork < max_fork_close) {

                //Questo if, controlla se la forca sia aperta del tutto e se la distanza tra la palla e il padre sia < 5.0
                if (actual_fork == 0 && check_distance_two_vectors(ball_object_to_be_taken, rotate_axis_fork_father, 5.0f)) {
                   
                    

                    //Qui vado a settare la matrice di posizione della palla, uguale a quella della ruota asse forca
                    ball_object_to_be_taken->set_pos_matrix(rotate_axis_fork_father->get_pos_matrix());

                    //Poi vado a settare la ruota asse forca come padre
                    ball_object_to_be_taken->set_parent(rotate_axis_fork_father);

                    //Dopo di che effettuo una traslazione perche altrimenti sarebbe dentro il padre
                    engine->translate_node("Sphere001", translate_ball);
                    
                    //Salvo un save point di come era originalmente la palla che viene usato dopo nella parte di release della palla
                    old_ball = ball_object_to_be_taken->get_pos_matrix();
                    
                    //flaggo a true il fatto che ho la palla grabbata
                    ball_grabbed = true;
                }
                

                //If che controlla se palla presa, e le forche sono <=2, posso chiudere ancora
                if (ball_grabbed && actual_fork <= 2) {
                    engine->scale_node("Sphere001", scale_ball);
                    engine->translate_node("forca1", -translate_fork);
                    engine->translate_node("forca2", translate_fork);
                    actual_fork++;
                }
                //Altrimenti controllo se ho o meno la palla e se non l'ho posso chiudere di piu le forche
                else if(!ball_grabbed) {
                    engine->translate_node("forca1", -translate_fork);
                    engine->translate_node("forca2", translate_fork);
                    actual_fork++;
                }
                
            }

            break;
        case 'z':
            engine->enableWireframe(true);
            break;
        case 'u':
            engine->enableWireframe(false);
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

    windowId = engine->init3Dcontext("Mangrovie Robotic Arm Project", 600, 600, argc, argv);
    
    Test* test = new Test();
    test->testExec();

    engine->setTextureFilePath("../files/textures/");
    engine->loadFromFile("../files/stanza.OVO");
    engine->setShadowFlag("Plane");

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
