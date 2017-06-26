#pragma once

#include <unordered_map>

#include "LarpPrerequisites.hpp"

namespace Larp
{
    /**
     * Used to load basic configurations such as screen width and height so that
     * recompiling for simple changes is not necessary.
     *
     * If there are additional options that the user would like to define in a
     * configuration file that are not defined in ConfigurationLoader::DEFAULTS,
     * then CustomConfigurationLoader should be used.
     */
    class ConfigurationLoader
    {
    private:
        /**
         * A map of pre-defined options, as well as their default values should
         * the user not provide them in the config file.
         */
        const std::unordered_map<std::string, std::string> c_defaults =
        {
            { "title",        "Default Title" },
            { "width",        "800" },
            { "height",       "600" },
            { "resizable",    "false" }
        };
        /**
         * Since we only want to load the configurations once, we make a static map between
         * ConfigurationLoaders. This way, the user can load as many configuration files
         * that they want for whatever purposes they have (e.g. a game that runs in two
         * separate windows).
         */
        static std::unordered_map<std::string, UniqueConfigurationLoader> s_loaded_configurations;
        /**
         * A map of (option -> value) that defines the configuration options provided
         * by the user in the config file.
         */
        std::unordered_map<std::string, std::string> m_configurations;
        /**
         * Loads the configuration options from the given configuration file.
         * @param path The path to the configuration file to load.
         * @note If options are provided that are not part of the pre-defined
         *       acceptable options, an error message is printed to the console,
         *       but execution will not be stopped.
         * @note If pre-defiined options are not given, then the default
         *       configurations defined in ConfigurationLoader::DEFAULTS for the
         *       missing options will be used.
         * @note If the given file cannot be opened, then all configurations
         *       defined in ConfigurationLoader::DEFAULTS will be used.
         */
        ConfigurationLoader(std::string path);
    public:
        /**
         * Loads a given configuration file
         * @param path The path to the configuration file to load.
         * @default If given no parameter, this function will attempt to load
         *          "larp.cfg", which it expects to find in the directory in which
         *          this program was run.
         * @note If options are provided that are not part of the pre-defined
         *       acceptable options, an error message is printed to the console,
         *       and the provided unacceptable option will be skipped,
         *       but execution will not be stopped.
         * @note If pre-defined options are not given, then the default
         *       configurations defined in ConfigurationLoader::DEFAULTS for the
         *       missing options will be used.
         * @note If the given file cannot be opened, then all configurations
         *       defined in ConfigurationLoader::DEFAULTS will be used.
         */
        static ConfigurationLoader* load_configurations(std::string path = "larp.cfg");
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
