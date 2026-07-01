#pragma once

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>

namespace SOGL {
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
    int getID() const;
    
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    void setMat4(const std::string& name, const float* matrix) const;
};
}
