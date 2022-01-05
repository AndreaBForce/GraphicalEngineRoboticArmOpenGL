#ifndef MESH_H
#define MESH_H
#include "Node.h"
#include "Material.h"

class Mesh : public Node
{
    public:
        Mesh();
        virtual ~Mesh();

        void render() override;
        Material* get_material();

        void load_mesh_from_file();

        //void set_material(Material new_material){material = new_material;}

        char meshName[FILENAME_MAX];
        glm::mat4 matrix;
        unsigned int children;
        char targetName[FILENAME_MAX];
        char subtypeName[FILENAME_MAX];
        char materialName[FILENAME_MAX];
        float radius;
        glm::vec3 bBoxMin;
        glm::vec3 bBoxMax;
        unsigned char hasPhysics;

    private:
        glm::vec4 texturingColoring;

        Material* material;

};

#endif // MESH_H
