#include "Texture.hpp"

namespace Larp
{
    std::unordered_map<std::string, UniqueTexture> Texture::_loaded_textures;

    Texture* Texture::create(std::string path, Type type)
    {
        if (_loaded_textures.find(path) == _loaded_textures.end())
        {
            _loaded_textures.emplace(path, UniqueTexture(new Texture(path, type)));
        }
        return _loaded_textures.at(path).get();
    }

    Texture::Texture(std::string path, Type type)
    {
        this->_path = path;
        this->_type = type;
        glGenTextures(1, &_id);
        int width, height;
        unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
        // Assign texture to ID
        glBindTexture(GL_TEXTURE_2D, _id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        SOIL_free_image_data(image);
    }

    std::string Texture::to_string()
    {
        if (this->_type == Texture::DIFFUSE)
            return "diffuse";
        if (this->_type == Texture::SPECULAR)
            return "specular";
        if (this->_type == Texture::REFLECTION)
            return "reflection";
        return "";
    }

    TextureID Texture::get_id()
    {
        return this->_id;
    }

    aiString& Texture::get_path()
    {
        return this->_path;
    }
}
