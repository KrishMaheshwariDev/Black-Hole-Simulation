#include "Logger.hpp"

#include <glad/glad.h>

#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <unordered_set>

namespace
{
    bool ShouldSuppressDuplicate(
        std::string_view level,
        std::string_view source,
        std::string_view message
    )
    {
        static std::mutex mutex;
        static std::unordered_set<std::string> seenMessages;

        const std::string key =
            std::string(level) + "|" +
            std::string(source) + "|" +
            std::string(message);

        std::lock_guard<std::mutex> lock(mutex);
        return !seenMessages.insert(key).second;
    }

    void LogMessage(
        std::ostream& stream,
        std::string_view level,
        std::string_view source,
        std::string_view message
    )
    {
        if ((level == "WARN" || level == "ERROR") &&
            ShouldSuppressDuplicate(level, source, message))
        {
            return;
        }

        stream << "[" << level << "][" << source << "] " << message << '\n';
    }

    std::string GetOpenGLErrorName(GLenum errorCode)
    {
        switch (errorCode)
        {
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW";
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";
        default:
            return "UNKNOWN_GL_ERROR";
        }
    }
}

void Core::Logger::Info(std::string_view source, std::string_view message)
{
    LogMessage(std::clog, "INFO", source, message);
}

void Core::Logger::Warn(std::string_view source, std::string_view message)
{
    LogMessage(std::clog, "WARN", source, message);
}

void Core::Logger::Error(std::string_view source, std::string_view message)
{
    LogMessage(std::cerr, "ERROR", source, message);
}

bool Core::Logger::LogOpenGLErrors(std::string_view source, std::string_view context)
{
    bool hasError = false;

    for (GLenum errorCode = glGetError(); errorCode != GL_NO_ERROR; errorCode = glGetError())
    {
        hasError = true;

        std::ostringstream message;
        message
            << context
            << " -> "
            << GetOpenGLErrorName(errorCode)
            << " ("
            << errorCode
            << ")";

        Error(source, message.str());
    }

    return hasError;
}
