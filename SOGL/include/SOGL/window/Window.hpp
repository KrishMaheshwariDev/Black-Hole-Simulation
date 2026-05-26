#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

class Window{
    private:
        GLFWwindow* window;
        int width, height;

    public:
        Window(int width, int height, const char* title);
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        Window(Window&& other) noexcept;
        Window& operator=(Window&& other) noexcept;

        bool shouldClose() const;

        void swapBuffers() const;
        void pollEvents() const;
        void clearColor() const;

        void processInput() const;

        GLFWwindow* getNativeWindow() const;
};