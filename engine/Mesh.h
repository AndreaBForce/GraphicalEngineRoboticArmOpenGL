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

        void load_mesh_from_file();

        void set_bBoxMin(glm::vec3 bBoxMin);
        void set_bBoxMax(glm::vec3 bBoxMax);
        void set_radius(float radius);
        void set_children(unsigned int children);
        void set_material(Material* new_material){material = new_material;}


        void addVertex(Vertex* vertex) { vertices.push_back(vertex); };
        void add_face(unsigned int* face) { faces.push_back(face); };
        std::vector<unsigned int*> getFaces(){return faces;};

    private:
        Material* material;
        char materialName[FILENAME_MAX];

        glm::vec3 bBoxMin;
        glm::vec3 bBoxMax;
        float radius;
        unsigned int children;
        std::vector<Vertex*> vertices;
        std::vector<unsigned int*> faces;
};

#endif // MESH_H
