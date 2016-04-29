#pragma once

#include "LarpPrerequisites.hpp"
#include "Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace Larp
{
    /**
     * A structure that stores information for each vertex in a model
     */
    struct Vertex
    {
        /**
         * The position of the Vertex
         */
        glm::vec3 _position;
        /**
         * The vertex normal for this Vertex
         */
        glm::vec3 _normal;
        /**
         * The (u, v) coordinate of the Texture for this Vertex
         */
        glm::vec2 _tex_coords;
    };

    class Texture
    {
    public:
        /**
         * Represents the possible types of Texture's that can be made
         */
        enum Type
        {
            DIFFUSE,
            SPECULAR
        };

        /**
         * The OpenGL texture ID
         */
        GLuint _id;
        /**
         * The Type of the texture. Used to determine what variable to attach the associated
         * Vertex object to in the fragment shader
         */
        Type _type;
        /**
         * File path to the Texture
         */
        aiString _path;
        /**
         * @return a string representation of this Texture's Type.
         */
        std::string to_string();
    };

    class Mesh
    {
    public:
        /**
         * The list of vertices associated with this Mesh. Used when binding the VBO.
         */
        std::vector<Vertex> _vertices;
        /**
         * The list of indices associated with this Mesh. Used when binding the EBO.
         */
        std::vector<GLuint> _indices;
        /**
         * The list of textures associated with this Mesh.
         */
        std::vector<Texture> _textures;
        /**
         * Constructor
         * @param vertices The list of vertices associated with this Mesh. Used for binding the VBO.
         * @param indices The list of indices associated with this Mesh. Used for binding the EBO.
         * @param textures The list of textures associated with this Mesh. Used for drawing textures.
         * @warning Meshes should @b not be created directly. Instead, a Mesh should be created by creating
         *          a Model.
         */
        Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
        /**
         * Draws the Mesh by binding the VAO's, VBO's, and EBO's associated with this Mesh.
         * @param shader The shader program to used to draw the Mesh
         * @warning This function should @b not be called directly as it is called by the Model draw function
         */
        void draw(Shader& shader);
        /**
         * Loads a texture from a file.
         * @param path The path to the texture that should be loaded.
         * @param directory The directory where the texture given in path is located.
         * @warning This function should @b not be called directory.
         */
        static GLint texture_from_file(const char* path, std::string directory);

    private:
        /**
         * Associated OpenGL VAO
         */
        GLuint _VAO;
        /**
         * Associated OpenGL VBO
         */
        GLuint _VBO;
        /**
         * Associated OpenGL EBO
         */
        GLuint _EBO;

        /**
         * Sets up this Meshes VAO, VBO, and EBO, and binds the vertices, indices, and textures
         * to OpenGL for rendering.
         */
        void setup_mesh();
    };
}


