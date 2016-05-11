#pragma once

#include <unordered_map>
#include <fstream>

#include "LarpPrerequisites.hpp"

namespace Larp
{
    /**
     * Used to load basic configurations such as screen width and height so that
     * recompiling for simple changes is not necessary.
     */
    class ConfigurationLoader
    {
    private:
        /**
         * A map of (option -> value) that defines the configuration options provided
         * by the user in the config file provided.
         */
        std::unordered_map<std::string, std::string> _settings;
        /**
         * A map of pre-defined options, as well as their default values should
         * the user not provide them in the config file.
         */
        static std::unordered_map<std::string, std::string> DEFAULTS;

    public:
        /**
         * Loads the configuration options from the given configuration file.
         * @param file_path The path to the configuration file to load.
         * @note If options are provided that are not part of the pre-defined
         *       acceptable options, an error message is printed to the console,
         *       but execution will not be stopped.
         * @note If pre-defiined options are not given, then the default
         *       settings defined in ConfigurationLoader::DEFAULTS for the
         *       missing options will be used.
         * @note If the given file cannot be opened, then all configurations
         *       defined in ConfigurationLoader::DEFAULTS will be used.
         */
        ConfigurationLoader(std::string file_path);
        /**
         * @return The title of the window either from the `title` option
         *         in the configuration file, or the `title` entry in DEFAULTS
         */
        std::string get_title() const;
        /**
         * @return The width of the window either from the `width` option
         *         in the configuration file, or the `width` entry in DEFAULTS
         */
        size_t get_width() const;
        /**
         * @return The height of the window either from the `height` option
         *         in the configuration file, or the `height` entry in DEFAULTS
         */
        size_t get_height() const;
        /**
         * @return The resizability of the window either from the `resizable` option
         *         in the configuration file, or the `resizable` entry in DEFAULTS
         */
        GLenum is_resizable() const;

        float get_music_volume() const;
        float get_sound_volume() const;
    };
}
