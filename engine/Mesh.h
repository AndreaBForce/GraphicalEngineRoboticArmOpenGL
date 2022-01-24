#ifndef MESH_H
#define MESH_H
#include "Node.h"
#include "Material.h"
#include "Vertex.h"
#include "Utils.h"
#include <string>

class LIB_API Mesh : public Node{
    public:
        Mesh();
        virtual ~Mesh();

        void render(glm::mat4 camera) override;

        Material* get_material();

        void loadMeshFromFile();

        void setChildren(unsigned int children);
        void setMaterial(Material* newMaterial){material = newMaterial;}
        void setHasShadow(bool flag){ hasShadow = flag;}

        unsigned int getChildren() { return this->children; };
        bool getHasShadow() { return this->hasShadow; };

        void addVertex(Vertex* vertex) { vertices.push_back(vertex); };
        void add_face(unsigned int* face) { faces.push_back(face); };
        std::vector<unsigned int*> getFaces(){return faces;};

    private:
        Material* material;
        char materialName[FILENAME_MAX];
        bool hasShadow;
        unsigned int children;
        std::vector<Vertex*> vertices;
        std::vector<unsigned int*> faces;

        void renderShadow(glm::mat4 camera);
};

#endif // MESH_H
