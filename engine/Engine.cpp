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

///////////////////
// BODY OF CLASS //
//////////////////

LIB_API Engine*  Engine::GetInstance(){
    if(engine_instance == nullptr){
        engine_instance = new Engine();
    }
    return engine_instance;
}

void LIB_API Engine::engineMsg(){
    std::cout << "Sono l'engine 1" << std::endl;
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
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
}

void LIB_API Engine::startEventLoop(){
    while(1){
        glutMainLoopEvent();

    }
}

void LIB_API Engine::endEventLoop(){
    glutLeaveMainLoop();
}

void LIB_API Engine::swapBuffer(){
    glutSwapBuffers();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This callback is invoked each time the window gets resized (and once also when created).
 * @param width new window width
 * @param height new window height
 */
void LIB_API reshapeCallback(int width, int height)
{
    std::cout << "[reshape func invoked]" << std::endl;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);
    glLoadMatrixf(glm::value_ptr(projection));
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

    glEnable(GL_DEPTH_TEST);

    return windowId;
}

void LIB_API Engine::loadTree(Node* root){
    Engine::engine_instance->rootE = root;
}
//C++->PREPROCESSOR->PREPROCESSOR DEFINITIONS-> METTI FREEGLUT_STATIC; davanti agli altri
//Linker->general_> additional librarys-> metti ..\dependencies\freeglut\lib\$(Platform)\$(Configuration);
//C++-> GENERAL -> ADDITIONAL SOCI -> metti ..\dependencies\freeglut\include;..\dependencies\glm\include

void LIB_API Engine::loadFromFile(const char* filePath) {

    //Declare the ovoreader
    OvoRReader OvoReader;

    Node* root = OvoReader.readDataFromFile(filePath);

    //TODO ASSIGN ROOT

}
