#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/string_cast.hpp>


#include "Engine.h"
#include "Node.h"
#include "Mesh.h"
#include "Light.h"

///////////////////////
// GLOBAL VARIABLES //
/////////////////////
int windowId;
Engine* engine;
Light* testL;
Mesh* testMesh;
float lightPosX = 0.0f;
float lightPosY = 5.0f;
float lightPosZ = 30.0f;


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
    //testL->setPosition(glm::vec3(lightPosX, lightPosY, lightPosZ));
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

bool check_distance_two_vectors(Node* node1,Node* node2,float range) {
    
    //L'ultima colonna delle final matrix contiene i vettori in world cordinates cosi possiamo confrontarli

    glm::vec4 node1_world_coordinate = glm::column(node1->get_final_matrix(), 3);
    glm::vec4 node2_world_coordinate = glm::column(node2->get_final_matrix(), 3);

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

    glm::vec3 scale_ball(1.25f, 1.0f, 1.0f);

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
            break;

        case 'n':
            //Down
            std::cout << "N PRESSED" << std::endl;
            engine->rotate_node("RuotaAsseForca", -0.5f, rotateAxisZ);
            break;
        case 'j':
            //apri pinza
            std::cout << "J PRESSED" << std::endl;


            if (actual_fork >= 0) {
                if (ball_grabbed) {
                    ball_object_to_be_taken = (dynamic_cast<Node*>(engine->get_object_list()->get_element_by_name("Sphere001")));
                    ball_object_to_be_taken->set_pos_matrix(old_ball);
                }
                if (actual_fork == 0 && ball_grabbed) {
                    //release ball
                    ball_object_to_be_taken = (dynamic_cast<Node*>(engine->get_object_list()->get_element_by_name("Sphere001")));
                    
                    
                    glm::vec4 ball_world_coordinate = glm::column(ball_object_to_be_taken->get_final_matrix(), 3);
                    glm::mat4 ball_pos_mat = ball_object_to_be_taken->get_pos_matrix();
                    
                  
                    glm::mat4 matriceInzialeePalle = glm::translate(glm::mat4(1.0f), glm::vec3(ball_world_coordinate.r, ball_world_coordinate.g, ball_world_coordinate.b));
                    glm::mat4 matriceFinalePalle = glm::translate(glm::mat4(1.0f), glm::vec3(ball_world_coordinate.r, 1.0f, ball_world_coordinate.b));
                   

                    // while per fare l'animazione di caduta palla
                    //E' un po buggato se ruoti l'asse della forca
                    while (ball_world_coordinate.g >= 1) {
                   

                        ball_pos_mat = ball_object_to_be_taken->get_pos_matrix();
                        ball_object_to_be_taken->set_pos_matrix(glm::translate(ball_pos_mat, -translate_ball_floor));
                        
                        ball_world_coordinate = glm::column(ball_object_to_be_taken->get_final_matrix(), 3);

                        displayCallback();
                       
                    }
                    
                    
                    std::cout << glm::to_string(matriceFinalePalle) << std::endl;
                    ball_object_to_be_taken->set_pos_matrix(matriceFinalePalle);

                    ball_object_to_be_taken->set_parent(engine->getRoot());
                   
                    ball_grabbed = false;
                }

               
                engine->translate_node("forca1", translate_fork);
                engine->translate_node("forca2", -translate_fork);
                
                actual_fork--;
            }
            break;

        case 'k':
            //chiud pinza
            std::cout << "K PRESSED" << std::endl;
            ball_object_to_be_taken = (dynamic_cast<Node*>(engine->get_object_list()->get_element_by_name("Sphere001")));
            rotate_axis_fork_father = (dynamic_cast<Node*>(engine->get_object_list()->get_element_by_name("RuotaAsseForca")));
            


            if (actual_fork < max_fork_close) {

                if (actual_fork == 0 && check_distance_two_vectors(ball_object_to_be_taken, rotate_axis_fork_father, 5.0f)) {
                   
                    ball_object_to_be_taken->set_pos_matrix(rotate_axis_fork_father->get_pos_matrix());
                    ball_object_to_be_taken->set_parent((dynamic_cast<Node*>(engine->get_object_list()->get_element_by_name("RuotaAsseForca"))));

                    engine->translate_node("Sphere001", translate_ball);
                    
                    old_ball = (dynamic_cast<Node*>(engine->get_object_list()->get_element_by_name("Sphere001"))->get_pos_matrix());
                    
                    ball_grabbed = true;
                }
                

                if (ball_grabbed && actual_fork <= 2) {
                    engine->scale_node("Sphere001", scale_ball);
                    engine->translate_node("forca1", -translate_fork);
                    engine->translate_node("forca2", translate_fork);
                    actual_fork++;
                }
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

    engine->setTextureFilePath("../files/textures/");
    engine->loadFromFile("../files/stanza.OVO");

    for(int i = 0; i < engine->getRoot()->get_number_of_children(); i++){
        std::cout << engine->getRoot()->getChildren().at(i)->get_name() << std::endl;
    }

    testL = dynamic_cast<Light*>(engine->getRoot()->getChildren().at(5));
    //testMesh = dynamic_cast<Mesh*>(engine->getRoot()->getChildren().at(0));
    testMesh = dynamic_cast<Mesh*>(engine->get_object_list()->get_list().at(16));

    //testMesh->render();

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
