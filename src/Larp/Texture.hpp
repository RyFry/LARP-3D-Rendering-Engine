#pragma once

#include <string>
#include <unordered_map>

#include "LarpPrerequisites.hpp"

namespace Larp
{
    class Texture
    {
    public:
        /**
         * Represents the possible types of Texture's that can be made
         */
        enum Type
        {
            DIFFUSE,
            SPECULAR,
            REFLECTION
        };
    private:
        /**
         * A cache of loaded Textures.
         */
        static std::unordered_map<std::string, UniqueTexture> _loaded_textures;

        Texture(std::string path);

        /**
         * The OpenGL texture ID
         */
        TextureID _id;
        /**
         * The Type of the texture. Used to determine what variable to attach the associated
         * Vertex object to in the fragment shader
         */
        Type _type;
        /**
         * File path to the Texture
         */
        aiString _path;
    public:
        static TexturePtr create(std::string path);
        /**
         * @return a string representation of this Texture's Type.
         */
        std::string to_string();
        TextureID get_id();
        aiString& get_path();
    };
}
