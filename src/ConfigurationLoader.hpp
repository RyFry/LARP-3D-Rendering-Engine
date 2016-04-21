#pragma once

#include <unordered_map>
#include <fstream>

#include "LarpPrerequisites.hpp"

namespace Larp
{
    class ConfigurationLoader
    {
    private:
        std::unordered_map<std::string, std::string> _settings;
        static std::unordered_map<std::string, std::string> DEFAULTS;

    public:
        ConfigurationLoader(std::string file_path);
        std::string get_title() const;
        size_t get_width() const;
        size_t get_height() const;
        GLenum is_resizable() const;
    };
}
