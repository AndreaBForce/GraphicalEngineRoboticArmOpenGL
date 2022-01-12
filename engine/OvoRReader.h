#include "Node.h"
#include "Light.h"
#include "Camera.h"
#include "Mesh.h"
#include "Utils.h"
#include <cstdint>
#include "List.h"

#ifndef OVOREADER_H
#define OVOREADER_H


// Stripped-down redefinition of OvObject (just for the chunk IDs):
class LIB_API OvObject
{
public:
    enum class Type : int  ///< Type of entities
    {
        // Foundation types:
        OBJECT = 0,
        NODE,
        OBJECT2D,
        OBJECT3D,
        LIST,

        // Derived classes:
        BUFFER,
        SHADER,
        TEXTURE,
        FILTER,
        MATERIAL,
        FBO,
        QUAD,
        BOX,
        SKYBOX,
        FONT,
        CAMERA,
        LIGHT,
        BONE,
        MESH,	   // Keep them...
        SKINNED, // ...consecutive        
        INSTANCED,
        PIPELINE,
        EMITTER,

        // Animation type
        ANIM,

        // Physics related:
        PHYSICS,

        // Terminator:
        LAST,
    };
};

// Stripped-down redefinition of OvMesh (just for the subtypes):
class LIB_API OvMesh
{
public:
    enum class Subtype : int ///< Kind of mesh
    {
        // Foundation types:
        DEFAULT = 0,
        NORMALMAPPED,
        TESSELLATED,

        // Terminator:
        LAST,
    };
};

// Stripped-down redefinition of OvLight (just for the subtypes):
class LIB_API OvLight
{
public:
    enum class Subtype : int ///< Kind of light
    {
        // Foundation types:
        OMNI = 0,
        DIRECTIONAL,
        SPOT,

        // Terminator:
        LAST,
    };
};


class LIB_API OvoRReader
{
public:
    Node* readDataFromFile(const char* filePath,List* list);
    Node* recursiveLoad(uint8_t* buffer, unsigned int& position);

private:

};


#endif // OvoRReader