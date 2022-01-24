#include "Node.h"
#include "Utils.h"

#ifndef CAMERA_H
#define CAMERA_H

class LIB_API Camera : public Node
{
    public:
        Camera();
        Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up) : eye{eye}, center{center}, up{up} {};
        virtual ~Camera();
        void render(glm::mat4 camera) override;

        glm::mat4 get_camera_mat();
        void set_eye(glm::vec3 eye){ this->eye = eye;};
        void set_center(glm::vec3 center){this->center = center;};
        void set_up(glm::vec3 up){this->up = up;};

    private:
        glm::mat4 view_matrix;
        glm::vec3 eye;
        glm::vec3 center;
        glm::vec3 up;

};
#endif // CAMERA_H
