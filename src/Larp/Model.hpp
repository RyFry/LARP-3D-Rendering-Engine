#pragma once

#include <unordered_map>        // std::unordered_map
#include <cfloat>               // FLT_MAX, FLT_MIN
#include <cmath>                // abs, exp
 
#include "LarpPrerequisites.hpp"
#include "Mesh.hpp"

namespace Larp
{
    class Model
    {
    public:
        /**
         * If the model at path is not already loaded, then it will be loaded and cached.
         * @param path The path to the desired model to be loaded.
         * @return A pointer to the Model specified by path.
         */
        static Model* create(std::string path);
        /**
         * Draws all of the meshes in this Model.
         * @param shader The shader program to render this Model with.
         */
        void draw(Shader& shader);
        /**
         *
         */
        const std::vector<Mesh>& get_meshes();
        GLfloat get_width() const;
        GLfloat get_height() const;
        GLfloat get_depth() const;
    private:
        /**
         * A cache of loaded Models.
         */
        static std::unordered_map<std::string, UniqueModel> s_loaded_models;
        /**
         * List of Meshes for this Model.
         */
        std::vector<Mesh> m_meshes;
        /**
         * The directory that this Model is stored in.
         */
        std::string m_directory;
        /**
         * List of Textures for each Mesh in this Model.
         */
        std::vector<Texture*> m_loaded_textures;
        /**
         * The width of the Model (measured along x-axis)
         */
        GLfloat m_width;
        /**
         * The height of the Model (measured along y-axis)
         */
        GLfloat m_height;
        /**
         * The depth of the Model (measured along z-axis)
         */
        GLfloat m_depth;
        /**
         * Default Constructor
         * @note This prevents users from creating Models.
         */
        Model();
        /**
         * Constructor
         * @param path Path to the model to load. Should be relative to where this application is run.
         */
        Model(std::string path);
        /**
         * Loads a Model given a path.
         * @param path The path to the model to load.
         */
        void load_model(std::string path);
        /**
         * Processes an aiNode and extracts the relevant model information.
         * @param node The aiNode to process.
         * @param scene The aiScene to retrieve Mesh information from.
         */
        void process_node(aiNode* node, const aiScene* scene);
        /**
         * Processes an aiMesh and extracts the relevant model information.
         * @param mesh The aiMesh to process.
         * @param scene The aiScene to retrieve Mesh information from.
         * @return The processed Mesh.
         */
        Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
        /**
         * Loads the textures for the material. After this function runs, this Model's s_loaded_textures
         * will be populated with all of the Textures necessary to render the Model.
         * @param mat The material to load textures for.
         * @param type The type of the texture to load. Should be one of aiTextureType_DIFFUSE,
         *             or aiTextureType_SPECULAR.
         * @param texture_type The type of the generated Texture object. Should be one of
         *                     Texture::DIFFUSE or Texture::SPECULAR.
         * @return A vector of loaded Textures
         * @note type and texture_type should both be the respective type (i.e. DIFFUSE or SPECULAR).
         */
        std::vector<Texture*> load_material_textures(aiMaterial* mat, aiTextureType type,
                                                    Texture::Type texture_type);
    };
}

