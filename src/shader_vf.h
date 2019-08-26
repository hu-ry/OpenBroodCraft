//
// Created by RH on 16.08.2019.
//
#ifndef OPENBROODCRAFT_SHADER_VF_H
#define OPENBROODCRAFT_SHADER_VF_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int ID;

    // constructor generates the shader on the fly
    Shader(const char* vertexPath, const char* fragmentPath) {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vertexShaderSource = vertexCode.c_str();
        const char* fragmentShaderSource = fragmentCode.c_str();

        // 2. compile shaders
        // declaring and initializing a Vertex Shader Object called vertexShader
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        // adding the shader source code to the shader object and compiling it
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        checkCompileErrors(vertexShader, "VERTEX");

        // declaring and initializing a Fragment Shader Object called fragmentShader
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        // adding the shader source code to the shader object and compiling it
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        checkCompileErrors(fragmentShader, "FRAGMENT");

        // shader Program
        // creating a program object with ID
        ID = glCreateProgram();
        // Attaching and linking the previously compiled shaders to the program
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);

        checkCompileErrors(ID, "PROGRAM");

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    // activate the shader
    void use() {
        glUseProgram(ID);
    }

    // utility uniform functions
    void setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void set4Float(const std::string &name, float value1, float value2, float value3, float value4) const {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
    }

    void setMatrix4fv(const std::string &name, int count, glm::mat4 valueMat4) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), count, GL_FALSE, glm::value_ptr(valueMat4));
    }

private:
    // utility function for checking shader compilation/linking errors.
    void checkCompileErrors(unsigned int shader, std::string type) {
        // checking if compilation was successful and if not what errors occurred.
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            // if failed, prints error message
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            // if failed, prints error message
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
#endif //OPENBROODCRAFT_SHADER_VF_H