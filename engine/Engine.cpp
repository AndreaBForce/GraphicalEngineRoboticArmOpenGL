#include "Engine.h"
#include "Node.h"

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


Engine* LIB_API Engine::GetInstance(){
    if(engine_instance == nullptr){
        engine_instance = new Engine();
    }

    return engine_instance;
}

void LIB_API Engine::engineMsg(){
    std::cout << "Sono l'engine 1" << std::endl;
}



float angle = 0.0f;
float distance = -45.0f;
int windowId;

void displayCallback()
{
    // Clear the screen:
    glClearColor(1.0f, 0.6f, 0.1f, 1.0f); // RGBA components
    glClear(GL_COLOR_BUFFER_BIT);

    // Set a matrix to move our triangle:
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, distance));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

    // Compute model matrix:
    glm::mat4 f = translation * rotationZ;

    glm::mat4 camera = glm::mat4(1.0f);


    // Set model matrix as current OpenGL matrix:
    glLoadMatrixf(glm::value_ptr(f));

    // Pass a triangle (object coordinates: the triangle is centered around the origin):
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-10.0f, -10.0f, 0.0f);
    glVertex3f(10.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    glEnd();

    // Swap this context's buffer:
    glutSwapBuffers();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This callback is invoked each time the window gets resized (and once also when created).
 * @param width new window width
 * @param height new window height
 */
void reshapeCallback(int width, int height)
{
    std::cout << "[reshape func invoked]" << std::endl;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);
    glLoadMatrixf(glm::value_ptr(projection));
    glMatrixMode(GL_MODELVIEW);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This callback is invoked each time a special keyboard key is pressed.
 * @param key key pressed id
 * @param mouseX mouse X coordinate
 * @param mouseY mouse Y coordinate
 */
void specialCallback(int key, int mouseX, int mouseY)
{
    std::cout << "[key pressed]" << std::endl;

    const float speed = 0.5f;
    switch (key)
    {
    case GLUT_KEY_UP:
        distance -= speed;
        break;

    case GLUT_KEY_DOWN:
        distance += speed;
        break;

    case GLUT_KEY_LEFT:
        angle += speed;
        break;

    case GLUT_KEY_RIGHT:
        angle -= speed;
        break;
    }

    // Force rendering refresh:
    glutPostWindowRedisplay(windowId);
}


void LIB_API Engine::init(const char* nomeFinestra, int width, int height, int argc, char* argv[]) {

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);

    glutInit(&argc, argv);

    // Set some optional flags:
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    // Create the window with a specific title:
    windowId = glutCreateWindow(nomeFinestra);

    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutSpecialFunc(specialCallback);

    glutMainLoop();
}

//C++->PREPROCESSOR->PREPROCESSOR DEFINITIONS-> METTI FREEGLUT_STATIC; davanti agli altri
//Linker->general_> additional librarys-> metti ..\dependencies\freeglut\lib\$(Platform)\$(Configuration);
//C++-> GENERAL -> ADDITIONAL SOCI -> metti ..\dependencies\freeglut\include;..\dependencies\glm\include
