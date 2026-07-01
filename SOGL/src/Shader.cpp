#include "../include/SOGL/shaders/Shader.hpp"

#include "core/Logger.hpp"

namespace SOGL {
    std::string Shader::loadFile(const char* filePath){
    std::ifstream file(filePath);

    if(!file.is_open()){
        Core::Logger::Error("Shader", std::string("Failed to open file: ") + filePath);
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

Shader::Shader(const char* vertPath, const char* fragPath){
    std::string vCode = loadFile(vertPath);
    const char* vertSource = vCode.c_str();

    std::string fCode = loadFile(fragPath);
    const char* fragSource = fCode.c_str();

    unsigned int vertexShader, fragShader;
    int success;
    char infoLog[512];

    // shader compiling
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        Core::Logger::Error("Shader", std::string("Vertex compilation failed:\n") + infoLog);
    }

    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSource, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        Core::Logger::Error("Shader", std::string("Fragment compilation failed:\n") + infoLog);
    }

    // linking the shader program
    ID = glCreateProgram(); // ID of the custom program (unsigned int)
    glAttachShader( ID, vertexShader);
    glAttachShader(ID, fragShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        Core::Logger::Error("Shader", std::string("Program linking failed:\n") + infoLog);
    }

    glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

Shader::~Shader(){
    glDeleteProgram(ID);
}

void Shader::use() const{
    glUseProgram(ID);
}

int Shader::getID() const{
    return ID;
}

void Shader::setMat4(const std::string& name, const float* matrix) const{
    int location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        Core::Logger::Warn("Shader", std::string("Uniform not found: ") + name);
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void Shader::setFloat(const std::string& name, float value) const{
    int location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        Core::Logger::Warn("Shader", std::string("Uniform not found: ") + name);
        return;
    }
    glUniform1f(location, value);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const{
    int location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        Core::Logger::Warn("Shader", std::string("Uniform not found: ") + name);
        return;
    }
    glUniform3f(location, x, y, z);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const{
    int location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        Core::Logger::Warn("Shader", std::string("Uniform not found: ") + name);
        return;
    }
    glUniform4f(location, x, y, z, w);
}
}
