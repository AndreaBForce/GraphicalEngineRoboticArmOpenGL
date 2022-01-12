#include "Vertex.h"

LIB_API Vertex::Vertex(){

}

LIB_API Vertex::~Vertex(){

}

void LIB_API Vertex::setVertex(glm::vec3 vertex){
    this->vertex = vertex;
}
void LIB_API Vertex::setNormal(glm::vec4 normal){
    this->normal = normal;
}
void LIB_API Vertex::setUv(glm::vec2 uv){
    this->uv = uv;
}
