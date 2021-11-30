#ifndef LIGHT_H
#define LIGHT_H
#include "Node.h"


class Light : public Node{
public:
public:
    Light();
    virtual ~Light();

    //Add light settings

    void render() override;

private:
    glm::mat4 view_matrix;
};

#endif // LIGHT_H
