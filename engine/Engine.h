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

		
		//783 MAX Y(Sul mio pc) la x non son stato a guardare
		void write2DText(const char* text,float pos_x,float y_pos);
		void setTimerCallback(void(*callback)(int value),int time,int min_time);


		Node* getRoot() { return rootE; };

		void setProjection(glm::mat4 projectionMat) { projection = projectionMat; };
		void setOrtho(glm::mat4 orthoMat) { ortho = orthoMat; };

		glm::mat4 getProjection() { return projection; };
		glm::mat4 getOrtho() { return ortho; };

		Engine(Engine &other) = delete;
		void operator=(const Engine &) = delete;

        void loadFromFile(const char* filePath);
    private:
        Engine(){};
        Node* rootE;
		glm::mat4 projection;
		glm::mat4 ortho;
        static Engine* engine_instance;
};

Engine* Engine::engine_instance = nullptr;;

#endif // ENGINE_H_INCLUDED
