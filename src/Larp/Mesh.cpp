#include "Mesh.hpp"

namespace Larp
{
    // ----------------
    // Public Functions
    // ----------------

    Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture*>& textures) :
        m_vertices(vertices),
        m_indices(indices),
        m_textures(textures)
    {
        this->setup_mesh();
    }

    void Mesh::draw(Shader& shader)
    {
        GLuint diffuse_n = 1;
        GLuint specular_n = 1;
        // GLuint reflection_nr = 1; This isn't being used because reflection isn't really good for games
        for (GLuint i = 0; i < m_textures.size(); ++i)
        {
            glActiveTexture(GL_TEXTURE1 + i); // Activate the proper texture unit before binding
            // Retrieve the texture number (diffuseN or specularN)
            std::stringstream ss;
            std::string number;
            std::string name = m_textures.at(i)->to_string();
            if (name == "diffuse")
                ss << diffuse_n++;
            else if (name == "specular")
                ss << specular_n++;
            else if (name == "reflection")
                ss << specular_n++;
            else
            {
                PRINT_ERROR("Unsupported texture type provided. Skipping.");
                continue;
            }
            number = ss.str();

            glUniform1i(glGetUniformLocation(shader.m_program, ("material." + name + number).c_str()), i + 1);
            glBindTexture(GL_TEXTURE_2D, m_textures.at(i)->get_id());
        }
        glActiveTexture(GL_TEXTURE1);

        // Draw mesh
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    // -----------------
    // Private Functions
    // -----------------

    void Mesh::setup_mesh()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);

        // Vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) 0);

        // Vertex Normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, m_normal));

        // Texture Coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, m_tex_coords));

        glBindVertexArray(0);
    }

    Texture* Mesh::texture_from_file(const char* path, std::string directory, Texture::Type type)
    {
        //Generate texture ID and load texture data
        std::string filename(path);
        filename = directory + "/" + filename;
        return Texture::create(filename, type);
    }
}
