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
// CLASSES //
/////////////

#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

class LIB_API Engine{
    public:
        static Engine* GetInstance();
        void engineMsg();
		void init(const char* nomeFinestra, int width,int height, int argc, char* argv[]);
        void loadTree(Node* root);

		Engine(Engine &other) = delete;
		void operator=(const Engine &) = delete;

    private:
        Engine(){};
        Node* rootE;
        static Engine* engine_instance;
};

Engine* Engine::engine_instance = nullptr;;

#endif // ENGINE_H_INCLUDED
