#include "Engine.h"
#include "Node.h"
#include "OvoRReader.h"
//////////////
// #INCLUDE //
//////////////


   // GLM:
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// FreeGLUT:
#include <GL/freeglut.h>


// C/C++:
#include <iostream>

//////////////
// DLL MAIN //
//////////////

#ifdef _WINDOWS
#include <Windows.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * DLL entry point. Avoid to rely on it for easier code portability (Linux doesn't use this method).
 * @param instDLL handle
 * @param reason reason
 * @param _reserved reserved
 * @return true on success, false on failure
 */
int APIENTRY DllMain(HANDLE instDLL, DWORD reason, LPVOID _reserved)
{
    // Check use:
    switch (reason)
    {
        ///////////////////////////
    case DLL_PROCESS_ATTACH: //
        break;


        ///////////////////////////
    case DLL_PROCESS_DETACH: //
        break;
    }

    // Done:
    return true;
}
#endif

//FreeImage
#include <FreeImage.h>
//define static variable
Engine* Engine::engine_instance = nullptr;

///////////////////
// BODY OF CLASS //
//////////////////

LIB_API Engine*  Engine::GetInstance(){
    if(engine_instance == nullptr){
        engine_instance = new Engine();
    }
    return engine_instance;
}

void LIB_API Engine::clearDisplay(){
    //glClearColor(0.0f, 0.6f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LIB_API Engine::setDisplayCallback(void(* callback)(void)){
    glutDisplayFunc(callback);
}

void LIB_API Engine::setSpecialCallback(void(* callback)(int key, int mouseX, int mouseY)){
    glutSpecialFunc(callback);
}

void LIB_API Engine::setKeyboardCallback(void(* callback)(unsigned char key, int mouseX, int mouseY)){
    glutKeyboardFunc(callback);
}

void LIB_API Engine::forceRendering(int windowId){
    glutPostWindowRedisplay(windowId);
}

void LIB_API Engine::enableLightSystem(){
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
    glEnable(GL_LIGHTING);
    glEnable(LIGHT0);
    glEnable(LIGHT1);
}

void LIB_API Engine::startEventLoop(){

    while(1){
        glutMainLoopEvent();
    }
}

void LIB_API Engine::endEventLoop(){
    std::cout << "FREE ENGINE" << std::endl;
    glutLeaveMainLoop();
    FreeImage_DeInitialise();
    delete(nodeList);
}

void LIB_API Engine::swapBuffer(){
    glutSwapBuffers();
}

void LIB_API Engine::enableWireframe(bool enable){
    if(enable)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void LIB_API Engine::setShadowFlag(const char* noShadowName){
    std::string excludeName = noShadowName;

    for(auto& element : nodeList->getList()){

        if(dynamic_cast<Mesh*>(element)){
            std::string meshName = element->get_name();
            if(meshName.find(excludeName) == std::string::npos){
                Mesh* mesh = dynamic_cast<Mesh*>(element);
                mesh->setHasShadow(true);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This callback is invoked each time the window gets resized (and once also when created).
 * @param width new window width
 * @param height new window height
 */
void LIB_API reshapeCallback(int width, int height)
{

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    //glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);

    Engine::GetInstance()->setProjection(glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 500.0f));
    Engine::GetInstance()->setOrtho(glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f));

    Engine::GetInstance()->setHeight(height);
    Engine::GetInstance()->setWidth(width);

    glLoadMatrixf(glm::value_ptr(Engine::GetInstance()->getProjection()));
    glMatrixMode(GL_MODELVIEW);
}


void LIB_API Engine::setReshapeCallback(){
    glutReshapeFunc(reshapeCallback);
}


int LIB_API Engine::init3Dcontext(const char* nomeFinestra, int width, int height, int argc, char* argv[]) {
    int windowId;

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);

    glutInit(&argc, argv);

    // Set some optional flags:
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_EXIT);

    // Create the window with a specific title:
    windowId = glutCreateWindow(nomeFinestra);

    //set shadow properties
    shadowMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.001f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 1.0f));
    shadowMaterial = new Material();
    shadowMaterial->setAmbient(glm::vec3(0.0f, 0.0f, 0.0f));
    shadowMaterial->setEmission(glm::vec3(0.0f, 0.0f, 0.0f));
    shadowMaterial->setDiffuse(glm::vec3(0.0f, 0.0f, 0.0f));
    shadowMaterial->setSpecular(glm::vec3(0.0f, 0.0f, 0.0f));
    shadowMaterial->setShininess(1.0f);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    return windowId;
}

void LIB_API Engine::loadTree(Node* root){
    Engine::engine_instance->rootE = root;
}
//C++->PREPROCESSOR->PREPROCESSOR DEFINITIONS-> METTI FREEGLUT_STATIC; davanti agli altri
//Linker->general_> additional librarys-> metti ..\dependencies\freeglut\lib\$(Platform)\$(Configuration);
//C++-> GENERAL -> ADDITIONAL SOCI -> metti ..\dependencies\freeglut\include;..\dependencies\glm\include

void LIB_API Engine::loadFromFile(const char* filePath) {

    FreeImage_Initialise();

    //Declare the ovoreader
    OvoRReader OvoReader;

    Node* root = OvoReader.readDataFromFile(filePath, Engine::engine_instance->getRenderList());

    loadTree(root);

}

/**
* Va in su di 14 in 14 per dare uno spazio ottimale
*/
void LIB_API Engine::write2DText(const char* text, float pos_x, float pos_y) {
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(Engine::engine_instance->getOrtho()));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(glm::mat4(1.0f)));

    // Disable lighting before rendering 2D text:
    glDisable(GL_LIGHTING);

    // Write some text:
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(pos_x, pos_y);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char*)text);

    // Reactivate lighting:
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(Engine::engine_instance->getProjection()));
    glMatrixMode(GL_MODELVIEW);
}

void LIB_API Engine::setTimerCallback(void(*callback)(int value),int time,int min_time) {
   glutTimerFunc(time,callback,min_time);
}

void LIB_API Engine::rotateNode(const char* node_name, float angle, glm::vec3 axis) {
    Node* thisNode = dynamic_cast<Node*>(Engine::engine_instance->getRenderList()->getElementByName(node_name));

    thisNode->set_pos_matrix(glm::rotate(thisNode->get_pos_matrix(), glm::radians(angle), axis));
}

void LIB_API Engine::translateNode(const char* node_name, glm::vec3 axis) {
    Node* thisNode = dynamic_cast<Node*>(Engine::engine_instance->getRenderList()->getElementByName(node_name));

    thisNode->set_pos_matrix(glm::translate(thisNode->get_pos_matrix(), axis));
}

void LIB_API Engine::scaleNode(const char* node_name, glm::vec3 axis) {
    Node* thisNode = dynamic_cast<Node*>(Engine::engine_instance->getRenderList()->getElementByName(node_name));

    thisNode->set_pos_matrix(glm::scale(thisNode->get_pos_matrix(), axis));
}
