#include "Utils.h"
#include "Material.h"
#include "Mesh.h"
#include "Light.h"
#include "List.h"
#include "Texture.h"
#include "Vertex.h"
#include "Engine.h"
#include "Camera.h"
#include "Node.h"
#include "Object.h"

class LIB_API Test {
public:

    Test();
    virtual ~Test();
    
    void testLight();
    void testMaterial();
    void testVertex();
    void testMesh();
    void testList();
    void testCamera();
    void testTexture();
    void testNode();
    void testObject();

    void testExec();

private:

};
