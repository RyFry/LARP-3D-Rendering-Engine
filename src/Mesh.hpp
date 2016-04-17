#ifndef MESH_HPP
#define MESH_HPP

#include "LarpPrerequisites.hpp"
#include "Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace Larp
{
    struct Vertex
    {
        glm::vec3 mPosition;
        glm::vec3 mNormal;
        glm::vec2 mTexCoords;
    };

    class Texture
    {
    public:
        enum Type
        {
            DIFFUSE,
            SPECULAR
        };

        GLuint mID;
        Type mType;
        aiString mPath;

        std::string toString();
    };

    class Mesh
    {
    public:
        // Mesh data
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;
        Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
        void draw(Shader& shader);
    private:
        // Render data
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        // Functions
        void setupMesh();
    };
}

#endif


