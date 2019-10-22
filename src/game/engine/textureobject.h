//
// Created by RH on 20.08.2019.
//

#ifndef OPENBROODCRAFT_TEXTUREOBJECT_H
#define OPENBROODCRAFT_TEXTUREOBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include "../../libs/stb_image.h"

struct Texture {
    unsigned int id;
    std::string type;
};

class TextureObject {
public:
    unsigned int ID;
    const char* texturePath;

    TextureObject() = default;

    TextureObject(const char* texturePath) {
        this->texturePath = texturePath;
        std::cout << "texturePath: " << texturePath << std::endl;
        glGenTextures(1, &ID);

        int width, height, nrChannels;
        unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

        if (data) {
            GLenum format;

            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, ID);
            // load image, create texture and generate mipmaps
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            // set the texture wrapping parameters
            // set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_set_flip_vertically_on_load(true);
        } else {
            std::cout << "Failed to load texture" << this->texturePath << std::endl;
        }
        stbi_image_free(data);
    }
};


#endif //OPENBROODCRAFT_TEXTUREOBJECT_H
