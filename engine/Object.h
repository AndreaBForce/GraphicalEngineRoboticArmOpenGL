#ifndef OBJECT_H
#define OBJECT_H
#include "Utils.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class LIB_API Object
{
    public:

        Object();
        virtual ~Object();

        int get_id(){return id;}

        std::string get_name(){return name;}

        void set_name(std::string new_name){name = new_name;}

        virtual void render(glm::mat4 camera) = 0;

        
    private:
        int id;
        std::string name;


};

#endif // OBJECT_H
