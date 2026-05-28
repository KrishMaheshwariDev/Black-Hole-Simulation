#include "../include/SOGL/graphic/VertexArray.hpp"

namespace SOGL {
    VertexArray::VertexArray(){
    glGenVertexArrays(1, &id);
}

VertexArray::VertexArray(VertexArray&& other) noexcept : id(other.id){
    other.id = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
    if(this != &other){
        glDeleteVertexArrays(1, &id);

        id = other.id;
        other.id = 0;
    }
    return *this;
}

VertexArray::~VertexArray(){
    if(id != 0){
        glDeleteVertexArrays(1, &id);
    }
}

void VertexArray::bind() const{
    glBindVertexArray(id);
}

void VertexArray::unbind() const{
    glBindVertexArray(0);
}

void VertexArray::AddAttribute(
    GLuint index,
    GLint size,
    GLenum type,
    GLboolean normalized,
    GLsizei stride,
    const void* offset
    ){
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

}