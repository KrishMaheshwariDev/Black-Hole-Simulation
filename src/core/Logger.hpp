#pragma once

#include <string_view>

namespace Core
{
    class Logger
    {
    public:
        static void Info(std::string_view source, std::string_view message);
        static void Warn(std::string_view source, std::string_view message);
        static void Error(std::string_view source, std::string_view message);

        static bool LogOpenGLErrors(std::string_view source, std::string_view context);
    };
}
