#include "../include/SOGL/graphic/Buffer.hpp"

SOGL::Buffer::Buffer(GLenum target): target(target){
    glGenBuffers(1, &id);
}

SOGL::Buffer::Buffer(Buffer&& other) noexcept : id(other.id), target(other.target){
    other.id = 0; // preventing double deletes
}

SOGL::Buffer::~Buffer(){
    if(id != 0){
        glDeleteBuffers(1, &id);
    }
}

SOGL::Buffer& SOGL::Buffer::operator=(Buffer&& other) noexcept{
    if(this != &other){
        glDeleteBuffers(1, &id);

        id = other.id;
        target = other.target;

        other.id = 0;
    }
    return *this;
}

void SOGL::Buffer::bind() const{
    glBindBuffer(target, id);
}

void SOGL::Buffer::unbind() const{
    glBindBuffer(0, id);
}

void SOGL::Buffer::SetData(const void* data, size_t size, GLenum usage){
    glBufferData(target, size, data, usage);
}

