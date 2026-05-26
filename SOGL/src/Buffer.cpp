#include "../include/SOGL/graphic/Buffer.hpp"

Buffer::Buffer(GLenum target): target(target){
    glGenBuffers(1, &id);
}

Buffer::Buffer(Buffer&& other) noexcept : id(other.id), target(other.target){
    other.id = 0; // preventing double deletes
}

Buffer::~Buffer(){
    if(id != 0){
        glDeleteBuffers(1, &id);
    }
}

Buffer& Buffer::operator=(Buffer&& other) noexcept{
    if(this != &other){
        glDeleteBuffers(1, &id);

        id = other.id;
        target = other.target;

        other.id = 0;
    }
    return *this;
}

void Buffer::bind() const{
    glBindBuffer(target, id);
}

void Buffer::SetData(const void* data, size_t size, GLenum usage){
    glBufferData(target, size, data, usage);
}

