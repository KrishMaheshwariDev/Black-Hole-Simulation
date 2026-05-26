#pragma once

#include <glad/glad.h>
#include <iostream>
#include <vector>

class Buffer{
    private:
        GLuint id;
        GLenum target;

    public:
        Buffer(GLenum target);
        // delete the defualt??
        Buffer(Buffer&& other) noexcept;
        ~Buffer();

        // delete the defualt??
        Buffer& operator=(Buffer&& other) noexcept;

        // bind and unbind the buffer
        void bind() const;

        // Data and Data size for memory allocation
        void SetData(const void* data, size_t size, GLenum usage);
        template<typename T>
        void SetData(const std::vector<T>& data, GLenum usage){
            glBufferData(target, data.size() * sizeof(T), data.data(), usage);
        }

        // utils
        void SetSubData(const void* data, size_t size, size_t offset);

};