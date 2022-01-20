#pragma once


/////////////
// VERSION //
/////////////

#include "Node.h"
#include "Utils.h"
#include "List.h"
#include "Texture.h"
#include "Material.h"
/////////////
// DEFINE //
///////////

#define MAX_LIGHTS 2
#define LIGHT0 0x4000
#define LIGHT1 0x4001
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
        void setTextureFilePath(const char* dirPath){ Texture::setPath(dirPath);};
        void enableWireframe(bool enable);
        void setShadowFlag(const char* noShadowName);


		//783 MAX Y(Sul mio pc) la x non son stato a guardare
		//TODO FARE GET HEIGHT E GET WIDHT COSI PUOI FARLO
		void write2DText(const char* text,float pos_x,float y_pos);
		void setTimerCallback(void(*callback)(int value),int time,int min_time);


		Node* getRoot() { return rootE; };

		void setProjection(glm::mat4 projectionMat) { projection = projectionMat; };
		void setOrtho(glm::mat4 orthoMat) { ortho = orthoMat; };

		int get_width() { return width; };
		int get_height() { return height;};

		void set_width(int widthS) { width = widthS; };
		void set_height(int heightS) { height = heightS; };

		Material* getShadowMaterial(){return shadowMaterial;};
		List* get_object_list() { return nodeList; }

		void rotate_node(const char* node_name, float angle,glm::vec3 axis);
		void translate_node(const char* node_name, glm::vec3 axis);


		glm::mat4 getProjection() { return projection; };
		glm::mat4 getOrtho() { return ortho; };
		glm::mat4 getShadowMatrix(){return shadowMatrix;};

		Engine(Engine &other) = delete;
		void operator=(const Engine &) = delete;

        void loadFromFile(const char* filePath);
    private:
        Engine(){};
        Node* rootE;
		glm::mat4 projection;
		glm::mat4 ortho;
        Material* shadowMaterial;
        glm::mat4 shadowMatrix;
		int width;
		int height;

		List* nodeList = new List();

        static Engine* engine_instance;
};

#endif // ENGINE_H_INCLUDED
