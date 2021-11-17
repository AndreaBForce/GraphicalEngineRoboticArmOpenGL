#ifndef CAMERA_H
#define CAMERA_H
#include "Node.h"


class Camera : public Node
{
    public:
        Camera();
        virtual ~Camera();

    private:
        glm::mat4 view_matrix;
};

#endif // CAMERA_H
