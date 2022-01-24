#ifndef MESH_H
#define MESH_H
#include "Node.h"
#include "Material.h"
#include "Vertex.h"
#include "Utils.h"
#include <string>
#include <memory>

class LIB_API Mesh : public Node{
    public:
        Mesh();
        ~Mesh();

        void render(glm::mat4 camera) override;

        Material* get_material();

        void load_mesh_from_file();

        void set_bBoxMin(glm::vec3 bBoxMin);
        void set_bBoxMax(glm::vec3 bBoxMax);
        void set_radius(float radius);
        void set_children(unsigned int children);
        void set_material(std::shared_ptr<Material> new_material){materialPtr = new_material;};
        void setHasShadow(bool flag){ hasShadow = flag;};

        glm::vec3 getBoxMin() { return this->bBoxMin; };
        glm::vec3 getBoxMax() { return this->bBoxMax; };
        float getRadius() { return this->radius; };
        unsigned int getChildren() { return this->children; };
        bool getHasShadow() { return this->hasShadow; };

        void addVertex(Vertex* vertex) { vertices.push_back(vertex); };
        void add_face(unsigned int* face) { faces.push_back(face); };
        std::vector<unsigned int*> getFaces(){return faces;};

    private:
        std::shared_ptr<Material> materialPtr;
        char materialName[FILENAME_MAX];
        bool hasShadow;

        glm::vec3 bBoxMin;
        glm::vec3 bBoxMax;
        float radius;
        unsigned int children;
        std::vector<Vertex*> vertices;
        std::vector<unsigned int*> faces;

        void renderShadow(glm::mat4 camera);
};

#endif // MESH_H
