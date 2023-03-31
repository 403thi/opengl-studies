#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/*
    texture stuff
*/
class Texture
{
    public:
        int width, height, nrChannels;
        unsigned int ID;
        Texture(const char* texturePath, unsigned int glMode = GL_RGB)
        {
            unsigned char* textureData = stbi_load(texturePath, &width, &height, &nrChannels, 0);

            glGenTextures(1, &ID);
            glBindTexture(GL_TEXTURE_2D, ID);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, glMode, GL_UNSIGNED_BYTE, textureData);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(textureData);
        }
};