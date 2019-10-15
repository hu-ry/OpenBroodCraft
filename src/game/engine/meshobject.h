//
// Created by RH on 17.08.2019.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdarg.h>
#include <string>
#include <algorithm>

#include "shader_vf.h"
#include "textureobject.h"
#include "../../globalvar.h"

class MeshObject {
public:
    unsigned int VAO_ID;

    std::vector<glm::vec3> vertices;
    std::vector<TextureObject> textures;
    int sizeArray;

    MeshObject() = default;

    MeshObject(const char* objectdataPath, GLenum bufferusage, bool useInstancing, std::vector<TextureObject> _textures) {
        this->textures = _textures;
        this->instanceSize = 0;
        sizeArray = 0;

        std::string verticesData = readVerticesf(objectdataPath, &sizeArray);

        std::cout << "array_size: " << sizeArray << std::endl;

        float vDataf[sizeArray];

        std::string delimiter = ",";
        int k = 0;

        size_t pos = 0;
        while ((pos = verticesData.find(delimiter)) != std::string::npos) {
            vDataf[k] = stof(verticesData.substr(0, pos));
            std::cout << k << ".Value: " << vDataf[k] << std::endl;
            verticesData.erase(0, pos + delimiter.length());
            k++;
        }
        vDataf[k] = stof(verticesData.substr(0, pos));
        std::cout << k << ".Value: " << vDataf[k] << std::endl;

        vertices.reserve( ((sizeArray-(sizeArray/5*2))/3) * sizeof(glm::vec3));
        int j = 0;
        for(int i=1; i<=sizeArray; i++) {
            float temp = (i % 5) / 3;
            if(temp <= 1 && temp != 0) {
                vertices[j] = glm::vec3(vDataf[i-1], vDataf[i], vDataf[i+1]);
                i += 3;
                j++;
            }
        }
        // takes an ID for the vertex arrays called VAO and generates it
        glGenVertexArrays(1, &VAO_ID);
        // takes an ID for the buffers called VBO and EBO and generates them
        glGenBuffers(1, &VBO);
        // binding the Vertex Array Object
        glBindVertexArray(VAO_ID);

        // assigning a buffer type to VBO, which will let us configure the currently bound buffer (VBO)
        // by any calls on GL_ARRAY_BUFFER
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // copies the previously defined vertex data into the buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(vDataf), vDataf, bufferusage);

        // telling OpenGL how it should interpret the vertex data
        // position attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        // texture mapping attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));



        // unbinding the VAO so there won't happen any accidents of other VAO's getting modified on accident
        if(!useInstancing) {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            unbindVertexArray();
        }
    }

    MeshObject(GLenum buffermode, GLenum bufferusage) {
        // takes an ID for the vertex arrays called VAO and generates it
        glGenVertexArrays(1, &VAO_ID);
        // takes an ID for the buffers called VBO and EBO and generates them
        glGenBuffers(1, &VBO);
        // binding the Vertex Array Object
        glBindVertexArray(VAO_ID);

        float points[] = {0.0f, 0.0f, 0.0f};

        glBindBuffer(buffermode, VBO);
        // copies the previously defined vertex data into the buffer
        glBufferData(buffermode, sizeof(points), points, bufferusage);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        // unbinding the VAO so there won't happen any accidents of other VAO's getting modified on accident
        unbindVertexArray();
    }

    void draw(Shader shader) {
        unsigned int normalNr   = 1;

        for(unsigned int i = 0; i < textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);

            shader.setInt("textObj1", 0);

            glBindTexture(GL_TEXTURE_2D, textures[i].ID);
        }
        // start drawing the mesh
        glBindVertexArray(VAO_ID);
        glDrawArrays(GL_TRIANGLES, 0, (int)sizeArray/5);

        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
    }

    void drawInstanced(Shader shader) {
        unsigned int normalNr   = 1;

        for(unsigned int i = 0; i < textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);

            shader.setInt("textObj1", 0);

            glBindTexture(GL_TEXTURE_2D, textures[i].ID);
        }
        // start drawing the mesh
        glBindVertexArray(VAO_ID);
        glDrawArraysInstanced(GL_TRIANGLES, 0, (int)sizeArray/5, instanceSize);

        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
    }

    void drawGeoBox(Shader shader) {
        glBindVertexArray(VAO_ID);
        glDrawArrays(GL_POINTS, 0, 1);
        glBindVertexArray(0);
    }

    void initInstancing(glm::vec2 translations[MAX_MAP_SIZE], const unsigned int &size) {
        instanceSize = size;
        glGenBuffers(1, &instanceVBO);
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        if(size != MAX_MAP_SIZE) {
            glm::vec2 data[size];
            for(int i = 0; i < size; ++i) {
                data[i] = translations[i];
            }
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * size, &data[0], GL_STATIC_DRAW);
        } else {
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * size, &translations[0], GL_STATIC_DRAW);
        }
        glEnableVertexAttribArray(2);
        //TODO: read data into buffer
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribDivisor(2, 1);
        unbindVertexArray();
    }

    void unbindVertexArray() {
        glBindVertexArray(0);
    }

    void bindVertexArray() {
        glBindVertexArray(VAO_ID);
    }

    void deallocateVertexArrays() {
        glDeleteVertexArrays(1, &VAO_ID);
        glDeleteBuffers(1, &VBO);
    //    glDeleteBuffers(1, &EBO);
    }

private:
    unsigned int VBO;
    unsigned int instanceVBO;
    int instanceSize;


    std::string readVerticesf(const char* objectdataPath, int* sizeArray) {
        std::string verticesData;
        std::ifstream verticesFile;

        verticesFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        try {
            // open files
            verticesFile.open(objectdataPath);
            std::stringstream verticesStream;
            // read file's buffer contents into streams
            verticesStream << verticesFile.rdbuf();
            // close file handlers
            verticesFile.close();
            // convert stream into string
            verticesData = verticesStream.str();
        } catch (std::ifstream::failure e) {
            std::cout << "ERROR::VERTEXARRAYOBJECT::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        std::cout << "data: " << verticesData << std::endl;

        std::string stringData;

        size_t startPos = 0;
        std::string kmmDelim = ",";
        std::string smclnDelim = ";";
        std::string nwlnDelim = "\n";
        auto kmmPos = verticesData.find(kmmDelim, startPos);
        auto SmclnPos = verticesData.find(smclnDelim, startPos);
        auto nwlnPos = verticesData.find(nwlnDelim, startPos);

        while (kmmPos != std::string::npos) {
            if (kmmPos < SmclnPos && kmmPos < nwlnPos) {
                stringData += verticesData.substr(startPos, kmmPos - startPos) + ",";
                startPos = kmmPos + kmmDelim.length();
                kmmPos = verticesData.find(kmmDelim, startPos);
            } else {
                if (SmclnPos < kmmPos && SmclnPos < nwlnPos) {
                    stringData += verticesData.substr(startPos, SmclnPos - startPos) + ",";
                    startPos = SmclnPos + smclnDelim.length();
                    SmclnPos = verticesData.find(smclnDelim, startPos);
                } else {
                    stringData += verticesData.substr(startPos, nwlnPos - startPos) + ",";
                    startPos = nwlnPos + nwlnDelim.length();
                    nwlnPos = verticesData.find(nwlnDelim, startPos);
                }
            }
            if(kmmPos == std::string::npos) {
                stringData = stringData.substr(0,startPos-1);
            }
        }

        *sizeArray = std::count(stringData.begin(), stringData.end(), ',') + 1;

        std::cout << ",: " << kmmPos << std::endl;
        std::cout << ";: " << SmclnPos << std::endl;
        std::cout << "newline: " << nwlnPos << std::endl;
        std::cout << "startPos: " << startPos << std::endl;

        std::cout << stringData << std::endl;



        return stringData;
    }
};