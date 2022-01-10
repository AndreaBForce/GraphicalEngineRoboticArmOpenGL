#include "Node.h"
#include "Utils.h"

#ifndef CAMERA_H
#define CAMERA_H

class LIB_API Camera : public Node
{
    public:
        Camera();
        virtual ~Camera();

    private:
        glm::mat4 view_matrix;
};

#endif // CAMERA_H
