#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

#include "Object.h"
#include "Utils.h"

class LIB_API Vertex : public Object {
    public:
        Vertex();
        ~Vertex();
        void render(glm::mat4 camera) {};
        void setVertex(glm::vec3 vertex);
        void setNormal(glm::vec4 normal);
        void setUv(glm::vec2 uv);

        glm::vec3 getVertex(){return this->vertex;};
        glm::vec3 getNormal(){return this->normal;};
        glm::vec2 getUv(){return this->uv;};

    private:
        glm::vec3 vertex;
        glm::vec3 normal;
        glm::vec2 uv;
};


#endif // VERTEX_H_INCLUDED
