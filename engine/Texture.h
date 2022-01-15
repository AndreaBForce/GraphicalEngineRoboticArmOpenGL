#ifndef TEXTURE_H
#define TEXTURE_H
#include "Object.h"
#include "Utils.h"

class LIB_API Texture : public Object {
    public:

        static void setPath(const char* dirPath);

        Texture(char textureName[FILENAME_MAX]);
        ~Texture();

        void render(glm::mat4 camera) override;

	private:
        unsigned int textureId;
        static std::string path;

};

#endif // TEXTURE_H
