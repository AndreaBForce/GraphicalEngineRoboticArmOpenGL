#pragma once


/////////////
// VERSION //
/////////////

// Generic info:
   #define LIB_NAME      "Engine library v0.1a"          ///< Library credits
   #define LIB_VERSION   10                              ///< Library version (divide by 10)

#ifdef _WINDOWS
   // Export API:
   // Specifies i/o linkage (VC++ spec):
   #ifdef ENGINE_EXPORTS
		#define LIB_API __declspec(dllexport)
   #else
		#define LIB_API __declspec(dllimport)
   #endif
#else // Under Linux
   #define LIB_API  // Dummy declaration
#endif

#include "Node.h"

/////////////
// DEFINE //
///////////

#define KEY_UP GLUT_KEY_UP
#define KEY_DOWN GLUT_KEY_DOWN
#define KEY_LEFT GLUT_KEY_LEFT
#define KEY_RIGHT GLUT_KEY_RIGHT

/////////////
// CLASSES //
/////////////

#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

class LIB_API Engine{
    public:
        static Engine* GetInstance();
        void engineMsg();
		int init3Dcontext(const char* nomeFinestra, int width,int height, int argc, char* argv[]);
		void setDisplayCallback(void(* callback)(void));
		void setReshapeCallback();
		void setSpecialCallback(void(* callback)(int key, int mouseX, int mouseY));
		void setKeyboardCallback(void(* callback)(unsigned char key, int mouseX, int mouseY));
		void forceRendering(int windowId);
		void enableLightSystem();
		void startEventLoop();
		void endEventLoop();
		void clearDisplay();
		void swapBuffer();
        void loadTree(Node* root);

		Engine(Engine &other) = delete;
		void operator=(const Engine &) = delete;

        void loadFromFile(const char* filePath);
    private:
        Engine(){};
        Node* rootE;
        static Engine* engine_instance;
};

Engine* Engine::engine_instance = nullptr;;

#endif // ENGINE_H_INCLUDED
