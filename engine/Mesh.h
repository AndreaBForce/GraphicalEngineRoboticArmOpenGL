#ifndef MESH_H
#define MESH_H
#include "Node.h"
#include "Material.h"
#include <string>

class Mesh : public Node{
    public:
        Mesh();
        virtual ~Mesh();

        void render() override;
        Material* get_material();

        void load_mesh_from_file();

        void set_mesh_name(char* meshName);

        void set_matrix(glm::mat4 matrix);
        void set_bBoxMin(glm::vec3 bBoxMin);
        void set_bBoxMax(glm::vec3 bBoxMax);
        void set_radius(float radius);
        void set_children(unsigned int children);
        void set_subtype(char subtypeName[FILENAME_MAX]);
        void set_targetName(char targetName[FILENAME_MAX]);
        //void set_material(Material new_material){material = new_material;}

        char materialName[FILENAME_MAX];

    private:
        glm::vec4 texturingColoring;

        Material* material;
        glm::mat4 matrix;
        glm::vec3 bBoxMin;
        glm::vec3 bBoxMax;
        float radius;
        unsigned int children;
        char subtypeName[FILENAME_MAX];
        char targetName[FILENAME_MAX];
};

#endif // MESH_H
