#ifndef MESH_H
#define MESH_H
#include "Node.h"


class Mesh : public Node
{
    public:
        Mesh();
        virtual ~Mesh();

        void render() override;

        void load_mesh_from_file();

        //void set_material(Material new_material){material = new_material;}

    private:
        glm::vec4 texturingColoring;

        //Material material;

};

#endif // MESH_H
