#ifndef MODEL_HPP
#define MODEL_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"

class Model
{
public:
    // Functions
    Model(std::string path);
    void draw(Shader& shader);
private:
    // Model data
    std::vector<Mesh> _meshes;
    std::string _directory;
    std::vector<Texture> _loaded_textures;

    // Functions
    void load_model(std::string path);
    void process_node(aiNode* node, const aiScene* scene);
    Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> load_material_textures(aiMaterial* mat, aiTextureType type,
                                                Texture::Type textureType);
};

GLint texture_from_file(const char* path, std::string directory);

#endif
