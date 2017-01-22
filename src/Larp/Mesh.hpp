#pragma once

#include "LarpPrerequisites.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

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
        glm::vec3 m_position;
        /**
         * The vertex normal for this Vertex
         */
        glm::vec3 m_normal;
        /**
         * The (u, v) coordinate of the Texture for this Vertex
         */
        glm::vec2 m_tex_coords;
    };

    class Mesh
    {
    public:
        /**
         * The list of vertices associated with this Mesh. Used when binding the VBO.
         */
        std::vector<Vertex> m_vertices;
        /**
         * The list of indices associated with this Mesh. Used when binding the EBO.
         */
        std::vector<GLuint> m_indices;
        /**
         * The list of textures associated with this Mesh.
         */
        std::vector<Texture*> m_textures;
        /**
         * Constructor
         * @param vertices The list of vertices associated with this Mesh. Used for binding the VBO.
         * @param indices The list of indices associated with this Mesh. Used for binding the EBO.
         * @param textures The list of textures associated with this Mesh. Used for drawing textures.
         * @warning Meshes should @b not be created directly. Instead, a Mesh should be created by creating
         *          a Model.
         */
        Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture*>& textures);
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
        static Texture* texture_from_file(const char* path, std::string directory, Texture::Type type);

    private:
        /**
         * Associated OpenGL VAO
         */
        VAO m_VAO;
        /**
         * Associated OpenGL VBO
         */
        VBO m_VBO;
        /**
         * Associated OpenGL EBO
         */
        EBO m_EBO;

        /**
         * Sets up this Meshes VAO, VBO, and EBO, and binds the vertices, indices, and textures
         * to OpenGL for rendering.
         */
        void setup_mesh();
    };
}


