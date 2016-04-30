#include "ConfigurationLoader.hpp"

std::unordered_map<std::string, std::string> Larp::ConfigurationLoader::DEFAULTS = {
    { "title",     "Default Title" },
    { "width",     "800" },
    { "height",    "600" },
    { "resizable", "false" },
};

Larp::ConfigurationLoader::ConfigurationLoader(std::string file_path)
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
        PRINT_ERROR("Failed to read " << file_path << ", so default configuration options will be used : " << e.what());
    }

    /*
     * Next, go line by line and make sure that all of the options provided
     * are one of the allowed options.
     * If they are one of the allowed options, then add the option to the _settings field
     * If they are not one of the allowed options, then print an error message saying it's
     * being ignored
     */
    while (config_stream)
    {
        std::string option;
        std::string setting;
        config_stream >> option >> setting;

        // Avoid blank lines
        if (option == "")
            continue;

        if (Larp::ConfigurationLoader::DEFAULTS.find(option) == Larp::ConfigurationLoader::DEFAULTS.end())
        {
            PRINT_ERROR('`' << option << "` is not a valid configuration option. Ignoring.");
        }
        else
        {
            this->_settings[option] = setting;
        }
    }
}

std::string Larp::ConfigurationLoader::get_title() const
{
    // Was a title provided?
    if (this->_settings.find("title") == this->_settings.end())
    {
        std::cout << "`title` was not provided, providing default title of `"
                  << Larp::ConfigurationLoader::DEFAULTS.at("title")
                  << "`."
                  << std::endl;
        return Larp::ConfigurationLoader::DEFAULTS.at("title");
    }
    else
    {
        return this->_settings.at("title");
    }
}

size_t Larp::ConfigurationLoader::get_width() const
{
    // Was a width provided?
    if (this->_settings.find("width") == this->_settings.end())
    {
        std::cout << "`width` was not provided, providing default width of "
                  << Larp::ConfigurationLoader::DEFAULTS.at("width")
                  << std::endl;
        std::stringstream sstream(Larp::ConfigurationLoader::DEFAULTS.at("width"));
        size_t ret_val;
        sstream >> ret_val;
        return ret_val;
    }
    else
    {
        std::stringstream sstream(this->_settings.at("width"));
        size_t ret_val;
        sstream >> ret_val;
        return ret_val;
    }
}

size_t Larp::ConfigurationLoader::get_height() const
{
    // Was a height provided?
    if (this->_settings.find("height") == this->_settings.end())
    {
        std::cout << "`height` was not provided, providing default height of "
                  << Larp::ConfigurationLoader::DEFAULTS.at("height")
                  << std::endl;
        std::stringstream sstream(Larp::ConfigurationLoader::DEFAULTS.at("height"));
        size_t ret_val;
        sstream >> ret_val;
        return ret_val;
    }
    else
    {
        std::stringstream sstream(this->_settings.at("height"));
        size_t ret_val;
        sstream >> ret_val;
        return ret_val;
    }
}

GLenum Larp::ConfigurationLoader::is_resizable() const
{
    // Was a resizable provided?
    if (this->_settings.find("resizable") == this->_settings.end())
    {
        std::cout << "`resizable` was not provided, providing default resizable of "
                  << Larp::ConfigurationLoader::DEFAULTS.at("resizable")
                  << std::endl;
        return Larp::ConfigurationLoader::DEFAULTS.at("resizable") == "true" ? GL_TRUE : GL_FALSE;
    }
    else
    {
        return this->_settings.at("resizable") == "true" ? GL_TRUE : GL_FALSE;
    }
}
