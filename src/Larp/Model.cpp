#include "Model.hpp"

namespace Larp
{
    std::unordered_map<std::string, UniqueModel> Model::_loaded_models;

    // ----------------
    // Public functions
    // ----------------

    Model* Model::create(std::string path)
    {
        if (_loaded_models.find(path) == _loaded_models.end())
        {
            _loaded_models.emplace(path, UniqueModel(new Model(path)));
        }
        return _loaded_models.at(path).get();
    }

    void Model::draw(Shader& shader)
    {
        for (GLuint i = 0; i < this->_meshes.size(); ++i)
            this->_meshes.at(i).draw(shader);
    }

    const std::vector<Mesh>& Model::get_meshes()
    {
        return this->_meshes;
    }

    GLfloat Model::get_width() const
    {
        return this->_width;
    }

    GLfloat Model::get_height() const
    {
        return this->_height;
    }

    GLfloat Model::get_depth() const
    {
        return this->_depth;
    }

    // -----------------
    // Private functions
    // -----------------

    Model::Model(std::string path)
        : _width(0.0f),
          _height(0.0f),
          _depth(0.0f)
    {
        this->load_model(path);

        // Calculate the width, height and depth of the model
        GLfloat min_x = FLT_MAX;
        GLfloat min_y = FLT_MAX;
        GLfloat min_z = FLT_MAX;
        GLfloat max_x = FLT_MIN;
        GLfloat max_y = FLT_MIN;
        GLfloat max_z = FLT_MIN;

        for (auto& mesh : this->_meshes)
        {
            for (auto& vert : mesh._vertices)
            {
                if (vert._position.x < min_x)
                    min_x = vert._position.x;
                if (vert._position.x > max_x)
                    max_x = vert._position.x;
                if (vert._position.y < min_y)
                    min_y = vert._position.y;
                if (vert._position.y > max_y)
                    max_y = vert._position.y;
                if (vert._position.z < min_z)
                    min_z = vert._position.z;
                if (vert._position.z > max_z)
                    max_z = vert._position.z;
            }
        }

        this->_width = max_x - min_x;
        this->_height = max_y - min_y;
        this->_depth = max_z - min_z;
        std::cout << "Dimensions of " << path << ": ("
                  << this->_width << ", " << this->_height << ", " << this->_depth << ')' << std::endl;
    }

    void Model::load_model(std::string path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            PRINT_ERROR("ERROR::ASSIMP::" << importer.GetErrorString());
            return;
        }

        this->_directory = path.substr(0, path.find_last_of('/'));
        this->process_node(scene->mRootNode, scene);
    }

    void Model::process_node(aiNode* node, const aiScene* scene)
    {
        // Process all the node's meshes (if any)
        for(GLuint i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            this->_meshes.push_back(this->process_mesh(mesh, scene));
        }

        // Then do the same for each of its children
        for(GLuint i = 0; i < node->mNumChildren; i++)
        {
            this->process_node(node->mChildren[i], scene);
        }
    }

    Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture*> textures;

        // Process vertices
        for(GLuint i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            // Process vertex positions, normals and texture coordinates
            glm::vec3 vector;
            if (mesh->mVertices == NULL)
            {
                THROW_RUNTIME_ERROR("mesh->mVertices is NULL");
            }
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex._position = vector;

            if (mesh->mNormals == NULL)
            {
                THROW_RUNTIME_ERROR("mesh->mNormals is NULL");
            }
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex._normal = vector;

            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex._tex_coords = vec;
            }
            else
                vertex._tex_coords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }

        // Process indices
        for (GLuint i = 0; i < mesh->mNumFaces; ++i)
        {
            aiFace face = mesh->mFaces[i];
            for (GLuint j = 0; j < face.mNumIndices; ++j)
                indices.push_back(face.mIndices[j]);
        }

        // Process material
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<Texture*> diffuseMaps = this->load_material_textures(material,
                                                                             aiTextureType_DIFFUSE,
                                                                             Texture::DIFFUSE);
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            std::vector<Texture*> specularMaps = this->load_material_textures(material,
                                                                              aiTextureType_SPECULAR,
                                                                              Texture::SPECULAR);
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return Mesh(vertices, indices, textures);
    }

    std::vector<Texture*> Model::load_material_textures(aiMaterial* mat, aiTextureType type, Texture::Type texture_type)
    {
        std::vector<Texture*> textures;
        for (GLuint i = 0; i < mat->GetTextureCount(type); ++i)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            GLboolean skip = false;
            for (GLuint j = 0; j < this->_loaded_textures.size(); ++j)
            {
                if (this->_loaded_textures.at(i)->get_path() == str)
                {
                    textures.push_back(this->_loaded_textures.at(i));
                    skip = true;
                    break;
                }
            }

            if (!skip)
            {
                // If the texture isn't already loaded, load it
                Texture* texture = Mesh::texture_from_file(str.C_Str(), this->_directory, texture_type);
                textures.push_back(texture);
                this->_loaded_textures.push_back(texture); // Add to loaded textures
            }
        }

        return textures;
    }
}

