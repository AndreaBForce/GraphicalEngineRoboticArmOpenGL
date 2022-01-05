#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/freeglut.h>

class Object
{
    public:
        int get_id(){return id;}

        char* get_name(){return name;}

        void set_name(char* new_name){name = new_name;}

        virtual void render() = 0;

    private:
        int id;
        char* name;
};

#endif // OBJECT_H
