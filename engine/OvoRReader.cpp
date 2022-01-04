/**
 * @file		ovoreader.cpp
 * @brief	Minimal decoder for the OverVision Object (OVO) 3D file format
 *
 * @author	A. "Killer" Peternier (achille.peternier@supsi.ch), (C) 2013-2020
 * @editor	D. Moranda (diego.moranda@supsi.ch), (C) 2021-2022
 * @editor	M. Metaldi (matteo.metaldi@student.supsi.ch), (C) 2021-2022
 * @editor	A. Riccardi (andrea.riccardi@student.supsi.ch), (C) 2021-2022
 *
 *
 */

//VISUAL STUDIO FLAG PER EVITARE L'ERRORE DI UNSAFE
//TODO BASTA METTERLO NELLE FLAG IN COMPILAZIONE
#pragma warning(disable:4996)

#include "OvoRReader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits.h>

using namespace std;
Node* OvoRReader::readDataFromFile(const char* filePath)
{

    //Root of the tree
    Node* root;

    FILE* pFile;
    long lSize;
    uint8_t* buffer;
    size_t result;

    pFile = fopen(filePath, "rb");
    if (pFile == NULL) { fputs("File error", stderr); exit(1); }

    // obtain file size:
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);

    // allocate memory to contain the whole file:
    buffer = (uint8_t*)malloc(sizeof(uint8_t) * lSize);

    fread(buffer, sizeof(uint8_t), lSize, pFile);
    fclose(pFile);

    if (buffer == NULL) { fputs("Memory error", stderr); exit(2); }

    unsigned int position = 0;

    //std::cout << lSize;
    root = recursiveLoad(buffer, position);
    root->addChild(recursiveLoad(buffer,position));

    //TODO QUESTO ERA UN TEST PER VERIFICARE CHE LEGGESSE IL TUTTO
    //VA RIMPIAZZATO CON LA RICORSIONE SOTTO
    /*for (int i = 0; i < 50; i++) {
        std::cout << "entro qua ora";

        root = recursiveLoad(buffer, position);
    }*/

    return root;
}

Node* OvoRReader::recursiveLoad(uint8_t* buffer, unsigned int& position)
{
    // Parse the chunk starting at buffer + position:
    // Extract node information
    Node* thisNode;
    unsigned int chunkId = 0, chunkSize = 0;
    unsigned int numberOfChildren = 0;

    /*
    * Leggi com memcpy e ogni volta poi sposti la position
    * Dopo ogni memcpy bisogna spostare la positon del socio
    */
    //Lettura id del chunk
    memcpy(&chunkId, buffer + position, sizeof(unsigned int));
    position = position + sizeof(unsigned int);

    //Lettura dimensione del chunk
    memcpy(&chunkSize, buffer + position, sizeof(unsigned int));
    position = position + sizeof(unsigned int);

    cout << "\nStampo l'id: " << chunkId;
    cout << "\nStampo il size: " << chunkSize;

    //Crazione del chunk di memoria e copia di dati
    //Qui abbiamo un altra position che é quella interna ovvero del chunck
    char* data = new char[chunkSize];
    unsigned int chunkPosition = 0;


    memcpy(data, buffer + position, sizeof(char) * chunkSize);
    position = position + (sizeof(char) * chunkSize);

    //TODO FARE UNA FUNZIONE DI STO MEGA PEZZO DI CODICE

    switch ((OvObject::Type)chunkId)
    {
        ///////////////////////////////
    case OvObject::Type::OBJECT: //
    {

        std::cout << "version]" << endl;
        // OVO revision number:
        unsigned int versionId = 0;
        memcpy(&versionId, data + chunkPosition, sizeof(unsigned int));
        cout << "   Version . . . :  " << versionId << endl;
        chunkPosition += sizeof(unsigned int);
        thisNode = new Node();

        //Credo che il primo Object che viene letto sia la root di tutto

    }
    break;


    /////////////////////////////
    case OvObject::Type::NODE: //
    {
        cout << "node]" << endl;

        // Node name:
        char nodeName[FILENAME_MAX];
        strcpy(nodeName, data + chunkPosition);
        cout << "   Name  . . . . :  " << nodeName << endl;
        chunkPosition += (unsigned int)strlen(nodeName) + 1;

        // Node matrix:
        glm::mat4 matrix;
        memcpy(&matrix, data + chunkPosition, sizeof(glm::mat4));

        chunkPosition += sizeof(glm::mat4);

        // Nr. of children nodes:
        unsigned int children;
        memcpy(&children, data + chunkPosition, sizeof(unsigned int));
        numberOfChildren = children;
        cout << "   Nr. children  :  " << children << endl;
        chunkPosition += sizeof(unsigned int);

        // Optional target node, [none] if not used:
        char targetName[FILENAME_MAX];
        strcpy(targetName, data + chunkPosition);
        cout << "   Target node . :  " << targetName << endl;
        chunkPosition += (unsigned int)strlen(targetName) + 1;
        thisNode = new Node();
    }
    break;


    /////////////////////////////////
    case OvObject::Type::MATERIAL: //
    {
        cout << "material]" << endl;
        Material* thisMaterial = new Material();

        // Material name:
        strcpy(thisMaterial->name, data + chunkPosition);
        cout << "   Name  . . . . :  " << (thisMaterial->name) << endl;
        chunkPosition += (unsigned int)strlen(thisMaterial->name) + 1;

        // Material term colors, starting with emissive:
        glm::vec3 emission, albedo;
        memcpy(&thisMaterial->emission, data + chunkPosition, sizeof(glm::vec3));
        cout << "   Emission  . . :  " << thisMaterial->emission.r << ", " << thisMaterial->emission.g << ", " << thisMaterial->emission.b << endl;
        chunkPosition += sizeof(glm::vec3);

        // Albedo:
        memcpy(&thisMaterial->albedo, data + chunkPosition, sizeof(glm::vec3));
        cout << "   Albedo  . . . :  " << thisMaterial->albedo.r << ", " << thisMaterial->albedo.g << ", " << thisMaterial->albedo.b << endl;
        chunkPosition += sizeof(glm::vec3);

        // Roughness factor:
        memcpy(&thisMaterial->roughness, data + chunkPosition, sizeof(float));
        cout << "   Roughness . . :  " << thisMaterial->roughness << endl;
        chunkPosition += sizeof(float);

        // Metalness factor:
        memcpy(&thisMaterial->metalness, data + chunkPosition, sizeof(float));
        cout << "   Metalness . . :  " << thisMaterial->metalness << endl;
        chunkPosition += sizeof(float);

        // Transparency factor
        memcpy(&thisMaterial->alpha, data + chunkPosition, sizeof(float));
        cout << "   Transparency  :  " << thisMaterial->alpha << endl;
        chunkPosition += sizeof(float);

        // Albedo texture filename, or [none] if not used:
        strcpy(thisMaterial->textureName, data + chunkPosition);
        cout << "   Albedo tex. . :  " << thisMaterial->textureName << endl;
        chunkPosition += (unsigned int)strlen(thisMaterial->textureName) + 1;

        // Normal map filename, or [none] if not used:
        strcpy(thisMaterial->normalMapName, data + chunkPosition);
        cout << "   Normalmap tex.:  " << thisMaterial->normalMapName << endl;
        chunkPosition += (unsigned int)strlen(thisMaterial->normalMapName) + 1;

        // Height map filename, or [none] if not used:
        strcpy(thisMaterial->heightMapName, data + chunkPosition);
        cout << "   Heightmap tex.:  " << thisMaterial->heightMapName << endl;
        chunkPosition += (unsigned int)strlen(thisMaterial->heightMapName) + 1;

        // Roughness map filename, or [none] if not used:
        strcpy(thisMaterial->roughnessMapName, data + chunkPosition);
        cout << "   Roughness tex.:  " << thisMaterial->roughnessMapName << endl;
        chunkPosition += (unsigned int)strlen(thisMaterial->roughnessMapName) + 1;

        // Metalness map filename, or [none] if not used:
        strcpy(thisMaterial->metalnessMapName, data + chunkPosition);
        cout << "   Metalness tex.:  " << thisMaterial->metalnessMapName << endl;
        chunkPosition += (unsigned int)strlen(thisMaterial->metalnessMapName) + 1;
    }
    break;


    ////////////////////////////////
    case OvObject::Type::MESH:    //
    case OvObject::Type::SKINNED:
    {
        // Both standard and skinned meshes are handled through this case:
        bool isSkinned = false;
        if ((OvObject::Type)chunkId == OvObject::Type::SKINNED)
        {
            isSkinned = true;
            cout << "skinned mesh]" << endl;
        }
        else
            cout << "mesh]" << endl;

        // Mesh name:
        char meshName[FILENAME_MAX];
        strcpy(meshName, data + chunkPosition);
        chunkPosition += (unsigned int)strlen(meshName) + 1;
        cout << "   Name  . . . . :  " << meshName << endl;

        // Mesh matrix:
        glm::mat4 matrix;
        memcpy(&matrix, data + chunkPosition, sizeof(glm::mat4));

        chunkPosition += sizeof(glm::mat4);

        // Mesh nr. of children nodes:
        unsigned int children;
        memcpy(&children, data + chunkPosition, sizeof(unsigned int));
        numberOfChildren = children;
        cout << "   Nr. children  :  " << children << endl;
        chunkPosition += sizeof(unsigned int);

        // Optional target node, or [none] if not used:
        char targetName[FILENAME_MAX];
        strcpy(targetName, data + chunkPosition);
        cout << "   Target node . :  " << targetName << endl;
        chunkPosition += (unsigned int)strlen(targetName) + 1;

        // Mesh subtype (see OvMesh SUBTYPE enum):
        unsigned char subtype;
        memcpy(&subtype, data + chunkPosition, sizeof(unsigned char));
        char subtypeName[FILENAME_MAX];
        switch ((OvMesh::Subtype)subtype)
        {
        case OvMesh::Subtype::DEFAULT: strcpy(subtypeName, "standard"); break;
        case OvMesh::Subtype::NORMALMAPPED: strcpy(subtypeName, "normal-mapped"); break;
        case OvMesh::Subtype::TESSELLATED: strcpy(subtypeName, "tessellated"); break;
        default: strcpy(subtypeName, "UNDEFINED");
        }
        cout << "   Subtype . . . :  " << (int)subtype << " (" << subtypeName << ")" << endl;
        chunkPosition += sizeof(unsigned char);

        // Material name, or [none] if not used:
        char materialName[FILENAME_MAX];
        strcpy(materialName, data + chunkPosition);
        cout << "   Material  . . :  " << materialName << endl;
        chunkPosition += (unsigned int)strlen(materialName) + 1;

        // Mesh bounding sphere radius:
        float radius;
        memcpy(&radius, data + chunkPosition, sizeof(float));
        cout << "   Radius  . . . :  " << radius << endl;
        chunkPosition += sizeof(float);

        // Mesh bounding box minimum corner:
        glm::vec3 bBoxMin;
        memcpy(&bBoxMin, data + chunkPosition, sizeof(glm::vec3));
        cout << "   BBox minimum  :  " << bBoxMin.x << ", " << bBoxMin.y << ", " << bBoxMin.z << endl;
        chunkPosition += sizeof(glm::vec3);

        // Mesh bounding box maximum corner:
        glm::vec3 bBoxMax;
        memcpy(&bBoxMax, data + chunkPosition, sizeof(glm::vec3));
        cout << "   BBox maximum  :  " << bBoxMax.x << ", " << bBoxMax.y << ", " << bBoxMax.z << endl;
        chunkPosition += sizeof(glm::vec3);

        // Optional physics properties:
        unsigned char hasPhysics;
        memcpy(&hasPhysics, data + chunkPosition, sizeof(unsigned char));
        cout << "   Physics . . . :  " << (int)hasPhysics << endl;
        chunkPosition += sizeof(unsigned char);
        if (hasPhysics)
        {
            /**
             * Mesh physics properties.
             */
            struct PhysProps
            {
                // Pay attention to 16 byte alignement (use padding):
                unsigned char type;
                unsigned char contCollisionDetection;
                unsigned char collideWithRBodies;
                unsigned char hullType;

                // Vector data:
                glm::vec3 massCenter;

                // Mesh properties:
                float mass;
                float staticFriction;
                float dynamicFriction;
                float bounciness;
                float linearDamping;
                float angularDamping;
                void* physObj;
                unsigned int nrOfHulls;
                void* hull;
                unsigned int _pad;
            };

            PhysProps mp;
            memcpy(&mp, data + chunkPosition, sizeof(PhysProps));
            chunkPosition += sizeof(PhysProps);
            cout << "      Type . . . :  " << (int)mp.type << endl;
            cout << "      Hull type  :  " << (int)mp.hullType << endl;
            cout << "      Cont. coll.:  " << (int)mp.contCollisionDetection << endl;
            cout << "      Col. bodies:  " << (int)mp.collideWithRBodies << endl;
            cout << "      Center . . :  " << mp.massCenter.x << ", " << mp.massCenter.y << ", " << mp.massCenter.z << endl;
            cout << "      Mass . . . :  " << mp.mass << endl;
            cout << "      Static . . :  " << mp.staticFriction << endl;
            cout << "      Dynamic  . :  " << mp.dynamicFriction << endl;
            cout << "      Bounciness :  " << mp.bounciness << endl;
            cout << "      Linear . . :  " << mp.linearDamping << endl;
            cout << "      Angular  . :  " << mp.angularDamping << endl;
            cout << "      Nr. hulls  :  " << mp.nrOfHulls << endl;

            // Custom hull(s) used?
            if (mp.nrOfHulls)
            {
                for (unsigned int c = 0; c < mp.nrOfHulls; c++)
                {


                    // Hull number of vertices:
                    unsigned int nrOfVertices;
                    memcpy(&nrOfVertices, data + chunkPosition, sizeof(unsigned int));

                    position += sizeof(unsigned int);

                    // Hull number of faces:
                    unsigned int nrOfFaces;
                    memcpy(&nrOfFaces, data + chunkPosition, sizeof(unsigned int));

                    position += sizeof(unsigned int);

                    // Hull centroid:
                    glm::vec3 centroid;
                    memcpy(&centroid, data + chunkPosition, sizeof(glm::vec3));

                    position += sizeof(glm::vec3);

                    // Iterate through hull vertices:
                    for (unsigned int c = 0; c < nrOfVertices; c++)
                    {
                        // Vertex coords:
                        glm::vec3 vertex;
                        memcpy(&vertex, data + chunkPosition, sizeof(glm::vec3));

                        chunkPosition += sizeof(glm::vec3);
                    }

                    // Iterate through hull faces:
                    for (unsigned int c = 0; c < nrOfFaces; c++)
                    {
                        unsigned int face[3];
                        memcpy(face, data + chunkPosition, sizeof(unsigned int) * 3);

                        chunkPosition += sizeof(unsigned int) * 3;
                    }
                }
            }
        }

        // Nr. of LODs:
        unsigned int LODs;
        memcpy(&LODs, data + chunkPosition, sizeof(unsigned int));
        cout << "   Nr. of LODs   :  " << LODs << endl;
        chunkPosition += sizeof(unsigned int);

        // For each LOD...:
        vector<unsigned int> verticesPerLOD(LODs); // Let's store this information for the skinned part, in case
        for (unsigned int l = 0; l < LODs; l++)
        {
            cout << "      LOD . . :  " << l + 1 << "/" << LODs << endl;

            // Nr. of vertices:
            unsigned int vertices, faces;
            memcpy(&vertices, data + chunkPosition, sizeof(unsigned int));
            cout << "   Nr. vertices  :  " << vertices << endl;
            chunkPosition += sizeof(unsigned int);
            verticesPerLOD[l] = vertices;

            // ...and faces:
            memcpy(&faces, data + chunkPosition, sizeof(unsigned int));
            cout << "   Nr. faces . . :  " << faces << endl;
            chunkPosition += sizeof(unsigned int);

            // Interleaved and compressed vertex/normal/UV/tangent data:
            for (unsigned int c = 0; c < vertices; c++)
            {


                // Vertex coords:
                glm::vec3 vertex;
                memcpy(&vertex, data + chunkPosition, sizeof(glm::vec3));
                chunkPosition += sizeof(glm::vec3);

                // Vertex normal:
                unsigned int normalData;
                memcpy(&normalData, data + chunkPosition, sizeof(unsigned int));

                chunkPosition += sizeof(unsigned int);

                // Texture coordinates:
                unsigned int textureData;
                memcpy(&textureData, data + chunkPosition, sizeof(unsigned int));

                chunkPosition += sizeof(unsigned int);

                // Tangent vector:
                unsigned int tangentData;
                memcpy(&tangentData, data + chunkPosition, sizeof(unsigned int));

                chunkPosition += sizeof(unsigned int);
            }

            // Faces:
            for (unsigned int c = 0; c < faces; c++)
            {
                // Face indexes:
                unsigned int face[3];
                memcpy(face, data + chunkPosition, sizeof(unsigned int) * 3);
                chunkPosition += sizeof(unsigned int) * 3;

            }
        }

        // Extra information for skinned meshes:
        if (isSkinned)
        {
            // Initial mesh pose matrix:
            glm::mat4 poseMatrix;
            memcpy(&poseMatrix, data + chunkPosition, sizeof(glm::mat4));

            chunkPosition += sizeof(glm::vec4);

            // Bone list:
            unsigned int nrOfBones;
            memcpy(&nrOfBones, data + chunkPosition, sizeof(unsigned int));
            cout << "   Nr. bones . . :  " << nrOfBones << endl;
            chunkPosition += sizeof(unsigned int);

            // For each bone...:
            for (unsigned int c = 0; c < nrOfBones; c++)
            {
                // Bone name:
                char boneName[FILENAME_MAX];
                strcpy(boneName, data + chunkPosition);
                cout << "      Bone name  :  " << boneName << " (" << c << ")" << endl;
                chunkPosition += (unsigned int)strlen(boneName) + 1;

                // Initial bone pose matrix (already inverted):
                glm::mat4 boneMatrix;
                memcpy(&boneMatrix, data + chunkPosition, sizeof(glm::mat4));

                chunkPosition += sizeof(glm::mat4);
            }

            // For each LOD...:
            for (unsigned int l = 0; l < LODs; l++)
            {
                cout << "      LOD . . :  " << l + 1 << "/" << LODs << endl;

                // Per vertex bone weights and indexes:
                for (unsigned int c = 0; c < verticesPerLOD[l]; c++)
                {


                    // Bone indexes:
                    unsigned int boneIndex[4];
                    memcpy(boneIndex, data + chunkPosition, sizeof(unsigned int) * 4);
                    chunkPosition += sizeof(unsigned int) * 4;

                    // Bone weights:
                    unsigned short boneWeightData[4];
                    memcpy(boneWeightData, data + chunkPosition, sizeof(unsigned short) * 4);

                    chunkPosition += sizeof(unsigned short) * 4;
                }
            }
        }
    }
    break;


    //////////////////////////////
    case OvObject::Type::LIGHT: //
    {
        cout << "light]" << endl;

        // Light name:
        char lightName[FILENAME_MAX];
        strcpy(lightName, data + chunkPosition);
        cout << "   Name  . . . . :  " << lightName << endl;
        chunkPosition += (unsigned int)strlen(lightName) + 1;

        // Light matrix:
        glm::mat4 matrix;
        memcpy(&matrix, data + chunkPosition, sizeof(glm::mat4));

        chunkPosition += sizeof(glm::mat4);

        // Nr. of children nodes:
        unsigned int children;
        memcpy(&children, data + chunkPosition, sizeof(unsigned int));
        numberOfChildren = children;
        cout << "   Nr. children  :  " << children << endl;
        chunkPosition += sizeof(unsigned int);

        // Optional target node name, or [none] if not used:
        char targetName[FILENAME_MAX];
        strcpy(targetName, data + chunkPosition);
        cout << "   Target node . :  " << targetName << endl;
        chunkPosition += (unsigned int)strlen(targetName) + 1;

        // Light subtype (see OvLight SUBTYPE enum):
        unsigned char subtype;
        memcpy(&subtype, data + chunkPosition, sizeof(unsigned char));
        char subtypeName[FILENAME_MAX];
        switch ((OvLight::Subtype)subtype)
        {
        case OvLight::Subtype::DIRECTIONAL: strcpy(subtypeName, "directional"); break;
        case OvLight::Subtype::OMNI: strcpy(subtypeName, "omni"); break;
        case OvLight::Subtype::SPOT: strcpy(subtypeName, "spot"); break;
        default: strcpy(subtypeName, "UNDEFINED");
        }
        cout << "   Subtype . . . :  " << (int)subtype << " (" << subtypeName << ")" << endl;
        chunkPosition += sizeof(unsigned char);

        // Light color:
        glm::vec3 color;
        memcpy(&color, data + chunkPosition, sizeof(glm::vec3));
        cout << "   Color . . . . :  " << color.r << ", " << color.g << ", " << color.b << endl;
        chunkPosition += sizeof(glm::vec3);

        // Influence radius:
        float radius;
        memcpy(&radius, data + chunkPosition, sizeof(float));
        cout << "   Radius  . . . :  " << radius << endl;
        chunkPosition += sizeof(float);

        // Direction:
        glm::vec3 direction;
        memcpy(&direction, data + chunkPosition, sizeof(glm::vec3));
        cout << "   Direction . . :  " << direction.r << ", " << direction.g << ", " << direction.b << endl;
        chunkPosition += sizeof(glm::vec3);

        // Cutoff:
        float cutoff;
        memcpy(&cutoff, data + chunkPosition, sizeof(float));
        cout << "   Cutoff  . . . :  " << cutoff << endl;
        chunkPosition += sizeof(float);

        // Exponent:
        float spotExponent;
        memcpy(&spotExponent, data + chunkPosition, sizeof(float));
        cout << "   Spot exponent :  " << spotExponent << endl;
        chunkPosition += sizeof(float);

        // Cast shadow flag:
        unsigned char castShadows;
        memcpy(&castShadows, data + chunkPosition, sizeof(unsigned char));
        cout << "   Cast shadows  :  " << (int)castShadows << endl;
        chunkPosition += sizeof(unsigned char);

        // Volumetric lighting flag:
        unsigned char isVolumetric;
        memcpy(&isVolumetric, data + chunkPosition, sizeof(unsigned char));
        cout << "   Volumetric  . :  " << (int)isVolumetric << endl;
        chunkPosition += sizeof(unsigned char);
    }
    break;


    /////////////////////////////
    case OvObject::Type::BONE: //
    {
        cout << "bone]" << endl;

        // Bone name:
        char boneName[FILENAME_MAX];
        strcpy(boneName, data + chunkPosition);
        cout << "   Name  . . . . :  " << boneName << endl;
        chunkPosition += (unsigned int)strlen(boneName) + 1;

        // Bone matrix:
        glm::mat4 matrix;
        memcpy(&matrix, data + chunkPosition, sizeof(glm::mat4));

        chunkPosition += sizeof(glm::mat4);

        // Nr. of children nodes:
        unsigned int children;
        memcpy(&children, data + chunkPosition, sizeof(unsigned int));
        numberOfChildren = children;
        cout << "   Nr. children  :  " << children << endl;
        chunkPosition += sizeof(unsigned int);

        // Optional target node, or [none] if not used:
        char targetName[FILENAME_MAX];
        strcpy(targetName, data + chunkPosition);
        cout << "   Target node . :  " << targetName << endl;
        chunkPosition += (unsigned int)strlen(targetName) + 1;

        // Mesh bounding box minimum corner:
        glm::vec3 bBoxMin;
        memcpy(&bBoxMin, data + chunkPosition, sizeof(glm::vec3));
        cout << "   BBox minimum  :  " << bBoxMin.x << ", " << bBoxMin.y << ", " << bBoxMin.z << endl;
        chunkPosition += sizeof(glm::vec3);

        // Mesh bounding box maximum corner:
        glm::vec3 bBoxMax;
        memcpy(&bBoxMax, data + chunkPosition, sizeof(glm::vec3));
        cout << "   BBox maximum  :  " << bBoxMax.x << ", " << bBoxMax.y << ", " << bBoxMax.z << endl;
        chunkPosition += sizeof(glm::vec3);
    }
    break;


    ///////////
    default: //
        cout << "UNKNOWN]" << endl;


        delete[] data;

    }



    buffer = buffer + position;
    delete[] data;

    // Go recursive when child nodes are avaialble:
    if (numberOfChildren){
        while (thisNode->getNrOfChildren() < numberOfChildren)
        {
            Node* childNode = recursiveLoad(buffer, position);
            thisNode->addChild(childNode);
        }
    }

    // Done:

    return thisNode;
}

