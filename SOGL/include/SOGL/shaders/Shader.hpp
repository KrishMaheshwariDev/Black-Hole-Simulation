#pragma once

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>

class Shader
{
private:
    unsigned int ID;

    std::string loadFile(const char* path);
    // void compileShader(unsigned int& shader, const char* source, unsigned int type);

public:
    Shader(const char* vertexPath, const char* fragPath);
    ~Shader();

    void use() const;
    
    void setFloat(const std::string& name, float value);
    void setVec3(const std::string& name, float x, float y, float z);
    void setMat4(const std::string& name, const float* matrix);
};

