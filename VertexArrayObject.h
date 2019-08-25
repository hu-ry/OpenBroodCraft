//
// Created by RH on 17.08.2019.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdarg.h>
#include <string>
#include <algorithm>

class VertexArrayObject {
public:
    unsigned int ID;

    VertexArrayObject(const char* objectdataPath, GLenum datatype, GLenum buffermode, GLenum bufferusage, bool enableTextures) {
        int amountArray = 0;
        std::string verticesData = readVerticesf(objectdataPath, &amountArray ,enableTextures);

        std::cout << "array_size: " << amountArray << std::endl;

        float vDataf[amountArray];

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

        glGenVertexArrays(1, &ID);
        glGenBuffers(1, &VBO);
    //    glGenBuffers(1, &EBO);

        // bind the Vertex Array Object first, then bind and set vertex buffer, and then configure vertex attributes.
        glBindVertexArray(ID);
        glBindBuffer(buffermode, VBO);
        glBufferData(buffermode, sizeof(vDataf), vDataf, bufferusage);

    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, bufferusage);

        glVertexAttribPointer(0, 3, datatype, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, datatype, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void unbindVertexArray() {
        glBindVertexArray(0);
    }

    void bindVertexArray() {
        glBindVertexArray(ID);
    }

    void deallocate() {
        glDeleteVertexArrays(1, &ID);
        glDeleteBuffers(1, &VBO);
    //    glDeleteBuffers(1, &EBO);
    }

private:
    unsigned int VBO;

    //unsigned int EBO;

    std::string readVerticesf(const char* objectdataPath, int *amountArray, bool enableTextures) {
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

        std::string stringData;

        int startPos = 0;
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
                if (enableTextures) {
                    if (SmclnPos < kmmPos && SmclnPos < nwlnPos) {
                        stringData += verticesData.substr(startPos, SmclnPos - startPos) + ",";
                        startPos = SmclnPos + smclnDelim.length();
                        SmclnPos = verticesData.find(smclnDelim, startPos);
                    } else {
                        stringData += verticesData.substr(startPos, nwlnPos - startPos) + ",";
                        startPos = nwlnPos + nwlnDelim.length();
                        nwlnPos = verticesData.find(nwlnDelim, startPos);
                    }
                } else {
                    if (nwlnPos != std::string::npos) {
                        stringData += verticesData.substr(startPos, SmclnPos - startPos) + ",";
                        startPos = nwlnPos + smclnDelim.length();
                        SmclnPos = verticesData.find(smclnDelim, startPos);
                    } else {
                        stringData += verticesData.substr(startPos, SmclnPos - startPos) + ",";
                        kmmPos = verticesData.find(smclnDelim, startPos);
                    }
                }
            }
            if(kmmPos == std::string::npos) {
                stringData = stringData.substr(0,startPos-1);
            }
        }

        *amountArray = std::count(stringData.begin(), stringData.end(), ',') + 1;

        std::cout << ",: " << kmmPos << std::endl;
        std::cout << ";: " << SmclnPos << std::endl;
        std::cout << "newline: " << nwlnPos << std::endl;

        std::cout << stringData << std::endl;



        return stringData;
    }
};