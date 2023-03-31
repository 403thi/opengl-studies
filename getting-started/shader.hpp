#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/*
    shader stuff
*/
class Shader
{
    private:
        unsigned int compileShader(unsigned int shaderType, std::string &shaderSource)
        {
            unsigned int shaderId = glCreateShader(shaderType);
            const char *source = shaderSource.c_str();
            glShaderSource(shaderId, 1, &source, NULL);
            glCompileShader(shaderId);

            int success;
            char infoLog[512];
            glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            return shaderId;
        }
    public:
        unsigned int ID;
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
        {
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;
            try
            {
                vShaderFile.open(vertexShaderPath);
                fShaderFile.open(fragmentShaderPath);

                std::stringstream vShaderStream, fShaderStream;
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();

                vShaderFile.close();
                fShaderFile.close();

                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            catch(std::ifstream::failure error)
            {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            }
            unsigned int vShaderID = compileShader(GL_VERTEX_SHADER, vertexCode);
            unsigned int fShaderID = compileShader(GL_FRAGMENT_SHADER, fragmentCode);
            ID = glCreateProgram();
            glAttachShader(ID, vShaderID);
            glAttachShader(ID, fShaderID);
            glLinkProgram(ID);

            int success;
            char infoLog[512];
            glGetProgramiv(ID, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(ID, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
            }
            glDeleteShader(vShaderID);
            glDeleteShader(fShaderID);
        }
        void use()
        {
            glUseProgram(ID);
        }
        void setBool(const std::string &name, bool value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
        }
        void setInt(const std::string &name, int value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
        }
        void setFloat(const std::string &name, float value) const
        {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
        }
        void setVec2(const std::string &name, float v1, float v2) const
        {
            glUniform2f(glGetUniformLocation(ID, name.c_str()), v1, v2);
        }
};

#endif