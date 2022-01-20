#include "Texture.h"
#include <GL/freeglut.h>
#include <FreeImage.h>
#include <iostream>

#define GL_TEXTURE_MAX_ANISOTROPY_EXT        0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT    0x84FF

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

//define static variable
std::string Texture::path;


LIB_API Texture::Texture(char textureName[FILENAME_MAX]) {

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    if(strstr((const char *)glGetString(GL_EXTENSIONS), "GL_EXT_texture_filter_anisotropic")){
        int ansiotropical_level;
        glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &ansiotropical_level);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ansiotropical_level);
    }

    std::string fullPath = path;
    fullPath.append(textureName);

    FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(fullPath.c_str(),0), fullPath.c_str());

    FreeImage_FlipVertical(bitmap);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), GL_BGRA_EXT, GL_UNSIGNED_BYTE, (void *)FreeImage_GetBits(bitmap));

    //glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(bitmap));

    FreeImage_Unload(bitmap);

}

LIB_API Texture::~Texture() {
}

void LIB_API Texture::setPath(const char* dirPath){
    path = dirPath;
}

void LIB_API Texture::render(glm::mat4 camera){
    glBindTexture(GL_TEXTURE_2D, textureId);
}
