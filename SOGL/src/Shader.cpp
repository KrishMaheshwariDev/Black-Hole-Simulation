#include "../include/SOGL/shaders/Shader.hpp"

std::string Shader::loadFile(const char* filePath){
    std::ifstream file(filePath);

    if(!file.is_open()){
        std::cout << "Error:  failed to open file\n";
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
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSource, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // linking the shader program
    ID = glCreateProgram(); // ID of the custom program (unsigned int)
    glAttachShader( ID, vertexShader);
    glAttachShader(ID, fragShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
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

void Shader::setMat4(const std::string& name, const float* matrix){
    int location = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void Shader::setFloat(const std::string& name, float value){
    int location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        std::cout << "Warning: uniform not found -> " << name << std::endl;
        return;
    }
    glUniform1f(location, value);
}

void Shader::setVec3(const std::string& name, float x, float y, float z){
    int location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        std::cout << "Warning: uniform not found -> " << name << std::endl;
        return;
    }
    glUniform3f(location, x, y, z);
}