#ifndef MESH_HPP
#define MESH_HPP

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

struct Vertex
{
    glm::vec3 _position;
    glm::vec3 _normal;
    glm::vec2 _tex_coords;
};

class Texture
{
public:
    enum Type
    {
        DIFFUSE,
        SPECULAR
    };

    GLuint _id;
    Type _type;
    aiString _path;

    std::string to_string();
};

class Mesh
{
public:
    // Mesh data
    std::vector<Vertex> _vertices;
    std::vector<GLuint> _indices;
    std::vector<Texture> _textures;
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
    void draw(Shader& shader);
private:
    // Render data
    GLuint _VAO;
    GLuint _VBO;
    GLuint _EBO;

    // Functions
    void setup_mesh();
};

#endif


