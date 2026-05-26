#include "../include/SOGL/window/Window.hpp"

// utils

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// class methods
Window::Window(int width, int height, const char* title): width(width), height(height){
    if(!glfwInit()){
        throw std::runtime_error("ERROR::WINDOW - GLFW initialization failed\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!window){
        throw std::runtime_error("ERROR::WINDOW - unable to create window\n");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        throw std::runtime_error("ERROR::WINDOW - unable to load GLAD\n");
    }

    glViewport(0, 0, width, height);
}

Window::~Window(){
    glfwDestroyWindow(window);
}

Window::Window(Window&& other) noexcept : window(other.window), width(other.width), height(other.height){
    other.window = nullptr;
}

Window& Window::operator=(Window&& other) noexcept{
    if(this != &other){
        if(window){
            glfwDestroyWindow(window);
        }
        window = other.window;
        width = other.width;
        height = other.height;

        other.window = nullptr;
    }
    return *this;
}

void Window::processInput() const{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

bool Window::shouldClose() const{
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() const{
    glfwSwapBuffers(window);
}

void Window::clearColor() const{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::pollEvents() const{
    glfwPollEvents();
}

GLFWwindow* Window::getNativeWindow() const{
    return window;
}