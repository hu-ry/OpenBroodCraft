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

    Shader() {}

    // constructor generates the shader on the fly
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr) {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
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
            // if geometry shader path is present, also load a geometry shader
            if(geometryPath != nullptr)
            {
                gShaderFile.open(geometryPath);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
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

        // if geometry shader is given, compile geometry shader
        unsigned int geometryShader;
        if(geometryPath != nullptr)
        {
            const char * gShaderCode = geometryCode.c_str();
            geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometryShader, 1, &gShaderCode, NULL);
            glCompileShader(geometryShader);
            checkCompileErrors(geometryShader, "GEOMETRY");
        }
        // shader Program
        // creating a program object with ID
        ID = glCreateProgram();
        // Attaching and linking the previously compiled shaders to the program
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        if(geometryPath != nullptr)
            glAttachShader(ID, geometryShader);
        glLinkProgram(ID);

        checkCompileErrors(ID, "PROGRAM");

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        if(geometryPath != nullptr)
            glDeleteShader(geometryShader);
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

    void set2Float(const std::string &name, float value1, float value2) const {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), value1, value2);
    }

    void set3Float(const std::string &name, float value1, float value2, float value3) const {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
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