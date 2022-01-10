#pragma once


/////////////
// VERSION //
/////////////

#include "Node.h"
#include "Utils.h"

/////////////
// DEFINE //
///////////

#define KEY_UP 0x0065
#define KEY_DOWN 0x0067
#define KEY_LEFT 0x0064
#define KEY_RIGHT 0x0066

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
