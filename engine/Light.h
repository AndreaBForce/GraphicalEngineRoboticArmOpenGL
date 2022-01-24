#include "Engine.h"

#ifndef LIGHT_H
#define LIGHT_H
#include "Node.h"
#include "Utils.h"
enum lightType{DIRECTIONAL = 0, OMNI, SPOT};


class LIB_API Light : public Node{
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

    glm::vec4 getAmbient();
    glm::vec4 getDiffuse();
    glm::vec4 getSpecular();
    glm::vec3 getDirection();
    float getCutoff();
    lightType getLightType();

    void render(glm::mat4 camera) override;

    uint16_t getLightNr(){return lightNr;};

private:
    glm::vec3 position ;
    glm::vec4 ambient ;
    glm::vec4 diffuse ;
    glm::vec4 specular ;
    glm::vec3 direction ;
    float cutoff ;
    lightType type;
    uint16_t lightNr;

    static int lightsCnt;
};

#endif // LIGHT_H
