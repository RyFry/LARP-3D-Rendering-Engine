#include "CustomConfigurationLoader.hpp"

#include <fstream>

namespace Larp
{
    std::unordered_map<std::string, UniqueCustomConfigurationLoader> CustomConfigurationLoader::s_loaded_configurations;

    CustomConfigurationLoader::CustomConfigurationLoader(std::string path, bool throw_if_failure)
    {
        // First, try to load the config file's contents into a string
        std::string config_lines;
        std::stringstream config_stream;
        std::ifstream config_file;
        config_file.exceptions(std::ifstream::badbit);
        try
        {
            // Open file
            config_file.open(path.c_str());
            // Read file's buffer contents into stream
            config_stream << config_file.rdbuf();
            // Close file handler
            config_file.close();
        }
        catch (std::ifstream::failure e)
        {
            if (throw_if_failure)
            {
                THROW_RUNTIME_ERROR("Failed to read `" << path << "`.");
            }
            else
            {
                PRINT_ERROR("Failed to read `" << path << "`.");
            }
        }

        // Next, go line by line and get the provided configurations.
        while (config_stream)
        {
            std::string configuration;
            std::string value;
            config_stream >> configuration >> value;

            // Avoid blank lines
            if (configuration == "")
                continue;

            // If the mapping (configuration -> somevalue) already exists, then emplace returns a pair
            // where the second value is false.
            auto is_emplaced = m_configurations.emplace(configuration, value);
            if (is_emplaced.second == false)
            {
                PRINT_ERROR("Could not insert `" << configuration << "` with value `" << value << "` because it already exists.");
            }
        }

        m_path = path;
    }

    CustomConfigurationLoader* CustomConfigurationLoader::load_configurations(std::string path, bool throw_if_failure)
    {
        if (s_loaded_configurations.find(path) == s_loaded_configurations.end())
        {
            s_loaded_configurations.emplace(path,
                                           UniqueCustomConfigurationLoader(new CustomConfigurationLoader(path, throw_if_failure)));
        }
        return s_loaded_configurations.at(path).get();
    }

    std::string CustomConfigurationLoader::get_configuration(std::string configuration)
    {
        if (m_configurations.find(configuration) == m_configurations.end())
        {
            PRINT_ERROR("Could not get configuration for configuration `" <<
                        configuration <<
                        "` because it was not found in `" <<
                        m_path <<
                        "`. Returning empty string.");
            return "";
        }
        else
        {
            return m_configurations.at(configuration);
        }
    }
}
