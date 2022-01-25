#include "Node.h"
#include "Utils.h"

#ifndef CAMERA_H
#define CAMERA_H

class LIB_API Camera : public Node
{
    public:
        Camera(){};
        Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up) : eye{eye}, center{center}, up{up} {};
        virtual ~Camera();

        glm::mat4 getCameraMat();
        void setEye(glm::vec3 eye){ this->eye = eye;};
        void setCenter(glm::vec3 center){this->center = center;};
        void setUp(glm::vec3 up){this->up = up;};

        glm::vec3 getEye(){return eye;};
        glm::vec3 getCenter(){return center;};
        glm::vec3 getUp(){return up;};

    private:
        glm::vec3 eye;
        glm::vec3 center;
        glm::vec3 up;

};
#endif // CAMERA_H
