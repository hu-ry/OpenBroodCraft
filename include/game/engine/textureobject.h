//
// Created by RH on 20.08.2019.
//

#ifndef OPENBROODCRAFT_TEXTUREOBJECT_H
#define OPENBROODCRAFT_TEXTUREOBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <algorithm>
#include "../../libs/stb_image.h"

struct Texture {
    unsigned int id;
    std::string type;
};

enum Orientation{
    TOP_UP = 0,
    TOP_LEFT,
    TOP_DOWN,
    TOP_RIGHT
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
        unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 4);


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

    TextureObject(const char* texturePath, Orientation alignment) {
        this->texturePath = texturePath;
        std::cout << "texturePath: " << texturePath << std::endl;
        glGenTextures(1, &ID);

        int width, height, nrChannels;
        unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 4);

        for(short i=alignment; i>0;i--)
        {
            rotateLeft(data, &width, &height, &nrChannels);
        }

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

private:
   /**
     * Rotate the image counter-clockwise to the left for 90 degree
    **/
   void rotateLeft(unsigned char* data, int* width, int* height, int* channels) {
       int img_size = *width * *height * *channels;
       size_t width_tmp = *width;
       size_t height_tmp = *height;
       unsigned char *datatmp = new stbi_uc[img_size];
        std::cout << sizeof(data) << "| datatmp:" << sizeof(datatmp) << img_size << std::endl;
       std::copy(data, data+img_size,datatmp);
       unsigned bytePerPixel = *channels;

       for(int j=0, destCol = *height; j < *height; ++j, --destCol)
       {
           int pixelOffset = *width * j;

           for(int i=0; i < *width; i++)
           {
               for (int k = 0; k < bytePerPixel; k++)
                   data[(i * *height + destCol) * bytePerPixel + k] = datatmp[(pixelOffset + i) * bytePerPixel + k];
           }
       }
       *width = height_tmp;
       *height = width_tmp;
       delete [] datatmp;
   }

    void fuckupImage(unsigned char* data, int* width, int* height, int* channels) {
        int img_size = *width * *height * *channels;
        size_t width_tmp = *width;
        size_t height_tmp = *height;
        unsigned char *datatmp = new unsigned char[img_size];
        std::cout << sizeof(data) << "| datatmp:" << sizeof(datatmp) << std::endl;
        std::copy(&data[0], &data[sizeof(data)],datatmp);

        for(int y=*height; y > 0; y--) {
            for(int x=*width; x > 0; x--) {
                data[((*width-(x-1)))*((*height-1)*4) + (*height-y)*4] = datatmp[((*height-y)*(*width*4)) + ((*width-x)*4)];
                data[(((*width-(x-1)))*((*height-1)*4) + (*height-y)*4)+1] = datatmp[(((*height-y)*(*width*4)) + ((*width-x)*4))+1];
                data[(((*width-(x-1)))*((*height-1)*4) + (*height-y)*4)+2] = datatmp[(((*height-y)*(*width*4)) + ((*width-x)*4))+2];
                data[(((*width-(x-1)))*((*height-1)*4) + (*height-y)*4)+3] = datatmp[(((*height-y)*(*width*4)) + ((*width-x)*4))+3];
            }
        }

        *width = height_tmp;
        *height = width_tmp;
        delete [] datatmp;
    }

};


#endif //OPENBROODCRAFT_TEXTUREOBJECT_H
