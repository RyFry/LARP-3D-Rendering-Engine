#pragma once

#include <unordered_map>
#include <fstream>

#include "Larp/LarpPrerequisites.hpp"

namespace Larp
{
    /**
     * CustomConfigurationLoader is a utility class with the purpose of
     * allowing the user to define custom configurations
     * (e.g. for sound, it is possible to define paths to sound effects, volume
     * levels, play channels, etc.).
     * This class cannot only load files of the form:
     *
     *    KEY1, STRING_VALUE1
     *    KEY2, STRING_VALUE2
     *
     * so if you need to load a key that maps to more than one value,
     * a user-made configuration loader would be best.
     */
    class CustomConfigurationLoader
    {
    private:
        /**
         * Since we only want to load the configurations once, we make a static map between
         * ConfigurationLoaders. This way, the user can load as many configuration files
         * that they want for whatever purposes they have (e.g. a game that runs in two
         * separate windows).
         */
        static std::unordered_map<std::string, UniqueCustomConfigurationLoader> s_loaded_configurations;
        /**
         * A map of (configuration -> value) that defines the configuration configurations provided
         * by the user in the config file.
         */
        std::unordered_map<std::string, std::string> m_configurations;
        /**
         * The path to the configuration file that was loaded
         */
        std::string m_path;
        /**
         * Loads the configuration configurations from the given configuration file.
         * @param path The path to the configuration file to load.
         * @param throw_if_failure If `true`, then the program will throw an error
         *                         if the file at path cannot be opened.
         *                         If `false`, then an error will be printed to the console,
         *                         but execution will continue.
         */
        CustomConfigurationLoader(std::string path, bool throw_if_failure);
    public:
        /**
         * Loads the configuration configurations from the given configuration file.
         * @param path The path to the configuration file to load.
         * @param throw_if_failure If `true`, then the program will throw an error
         *                         if the file at path cannot be opened.
         *                         If `false`, then an error will be printed to the console,
         *                         but execution will continue.
         * @default This function will not throw an error unless throw_if_failure is
         *          provided and has the value, `true`.
         */
        static CustomConfigurationLoader* load_configurations(std::string path, bool throw_if_failure = false);
        /**
         * Gets the value of the given configuration from this CustomConfigurationLoader
         * @param configuration The configuration to grab from this CustomConfigurationLoader.
         * @warning If `configuration` was not defined
         */
        std::string get_configuration(std::string configuration);
    };
}
