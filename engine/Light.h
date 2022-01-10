#ifndef LIGHT_H
#define LIGHT_H
#include "Node.h"

enum lightType{DIRECTIONAL = 0, OMNI, SPOT};


class Light : public Node{
public:
public:
    Light();
    virtual ~Light();

    //Add light settings
    void setPosition(glm::vec3 position);
    void setAmbient(glm::vec4 ambient);
    void setDiffuse(glm::vec4 diffuse);
    void setSpecular(glm::vec4 specular);
    void setDirection(glm::vec3 direction);
    void setCutoff(float cutoff);
    void setLightType(lightType type);

    void render() override;

private:
    glm::vec3 position ;
    glm::vec4 ambient ;
    glm::vec4 diffuse ;
    glm::vec4 specular ;
    glm::vec3 direction ;
    float cutoff ;
    lightType type;
};

#endif // LIGHT_H
