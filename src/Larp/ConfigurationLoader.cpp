#include "ConfigurationLoader.hpp"

#include <fstream>

namespace Larp
{
    std::unordered_map<std::string, UniqueConfigurationLoader> ConfigurationLoader::s_loaded_configurations;

    ConfigurationLoader::ConfigurationLoader(std::string file_path)
    {
        // First, try to load the config file's contents into a string
        std::string config_lines;
        std::stringstream config_stream;
        std::ifstream config_file;
        config_file.exceptions(std::ifstream::badbit);
        try
        {
            // Open file
            config_file.open(file_path.c_str());
            // Read file's buffer contents into stream
            config_stream << config_file.rdbuf();
            // Close file handler
            config_file.close();
        }
        catch (std::ifstream::failure e)
        {
            PRINT_ERROR("Failed to read `" << file_path << "`, so default configuration will be used : " << e.what());
        }

        /*
         * Next, go line by line and make sure that all of the configurations provided
         * are one of the allowed configurations.
         * If they are one of the allowed configurations, then add the configuration to the m_configurations field
         * If they are not one of the allowed configurations, then print an error message saying it's
         * being ignored
         */
        while (config_stream)
        {
            std::string configuration;
            std::string value;
            config_stream >> configuration >> value;

            // Avoid blank lines
            if (configuration == "")
                continue;

            if (Larp::ConfigurationLoader::c_defaults.find(configuration) == Larp::ConfigurationLoader::c_defaults.end())
            {
                PRINT_ERROR('`' << configuration << "` is not a valid configuration. Ignoring.");
            }
            else
            {
                // If the mapping (configuration -> somevalue) already exists, then emplace returns a pair
                // where the second value is false.
                auto is_emplaced = m_configurations.emplace(configuration, value);
                if (is_emplaced.second == false)
                {
                    PRINT_ERROR("Could not insert `" << configuration << "` with value `" << value << "` because it already exists.");
                }
            }
        }
    }

    ConfigurationLoader* ConfigurationLoader::load_configurations(std::string path)
    {
        if (s_loaded_configurations.find(path) == s_loaded_configurations.end())
        {
            s_loaded_configurations.emplace(path, UniqueConfigurationLoader(new ConfigurationLoader(path)));
        }
        return s_loaded_configurations.at(path).get();
    }

    std::string ConfigurationLoader::get_title() const
    {
        // Was a title provided?
        if (m_configurations.find("title") == m_configurations.end())
        {
            std::cout << "`title` was not provided, providing default title of `"
                      << Larp::ConfigurationLoader::c_defaults.at("title")
                      << "`."
                      << std::endl;
            return Larp::ConfigurationLoader::c_defaults.at("title");
        }
        else
        {
            return m_configurations.at("title");
        }
    }

    size_t ConfigurationLoader::get_width() const
    {
        // Was a width provided?
        if (m_configurations.find("width") == m_configurations.end())
        {
            std::cout << "`width` was not provided, providing default width of "
                      << Larp::ConfigurationLoader::c_defaults.at("width")
                      << std::endl;
            std::stringstream sstream(Larp::ConfigurationLoader::c_defaults.at("width"));
            size_t ret_val;
            sstream >> ret_val;
            return ret_val;
        }
        else
        {
            std::stringstream sstream(m_configurations.at("width"));
            size_t ret_val;
            sstream >> ret_val;
            return ret_val;
        }
    }

    size_t ConfigurationLoader::get_height() const
    {
        // Was a height provided?
        if (m_configurations.find("height") == m_configurations.end())
        {
            std::cout << "`height` was not provided, providing default height of "
                      << Larp::ConfigurationLoader::c_defaults.at("height")
                      << std::endl;
            std::stringstream sstream(Larp::ConfigurationLoader::c_defaults.at("height"));
            size_t ret_val;
            sstream >> ret_val;
            return ret_val;
        }
        else
        {
            std::stringstream sstream(m_configurations.at("height"));
            size_t ret_val;
            sstream >> ret_val;
            return ret_val;
        }
    }

    GLenum ConfigurationLoader::is_resizable() const
    {
        // Was a resizable provided?
        if (m_configurations.find("resizable") == m_configurations.end())
        {
            std::cout << "`resizable` was not provided, providing default resizable of "
                      << Larp::ConfigurationLoader::c_defaults.at("resizable")
                      << std::endl;
            return Larp::ConfigurationLoader::c_defaults.at("resizable") == "true" ? GL_TRUE : GL_FALSE;
        }
        else
        {
            return m_configurations.at("resizable") == "true" ? GL_TRUE : GL_FALSE;
        }
    }

    float ConfigurationLoader::get_music_volume() const
    {
        // Was a music_volume provided?
        if (m_configurations.find("music_volume") == m_configurations.end())
        {
            std::cout << "`music_volume` was not provided, providing default width of "
                      << Larp::ConfigurationLoader::c_defaults.at("music_volume")
                      << std::endl;
            std::stringstream sstream(Larp::ConfigurationLoader::c_defaults.at("music_volume"));
            float ret_val;
            sstream >> ret_val;
            return ret_val;
        }
        else
        {
            std::stringstream sstream(m_configurations.at("music_volume"));
            float ret_val;
            sstream >> ret_val;
            return ret_val;
        }
    }

    float ConfigurationLoader::get_sound_volume() const
    {
        // Was a music_volume provided?
        if (m_configurations.find("sound_volume") == m_configurations.end())
        {
            std::cout << "`sound_volume` was not provided, providing default width of "
                      << Larp::ConfigurationLoader::c_defaults.at("sound_volume")
                      << std::endl;
            std::stringstream sstream(Larp::ConfigurationLoader::c_defaults.at("sound_volume"));
            float ret_val;
            sstream >> ret_val;
            return ret_val;
        }
        else
        {
            std::stringstream sstream(m_configurations.at("sound_volume"));
            float ret_val;
            sstream >> ret_val;
            return ret_val;
        }
    }
}
