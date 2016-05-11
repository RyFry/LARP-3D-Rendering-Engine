#include "Mesh.hpp"

namespace Larp
{
    // ----------------
    // Public Functions
    // ----------------

    Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture*>& textures) :
        _vertices(vertices),
        _indices(indices),
        _textures(textures)
    {
        this->setup_mesh();
    }

    void Mesh::draw(Shader& shader)
    {
        GLuint diffuseN = 1;
        GLuint specularN = 1;
        GLuint reflectionNr = 1;
        for (GLuint i = 0; i < this->_textures.size(); ++i)
        {
            glActiveTexture(GL_TEXTURE1 + i); // Activate the proper texture unit before binding
            // Retrieve the texture number (diffuseN or specularN)
            std::stringstream ss;
            std::string number;
            std::string name = this->_textures.at(i)->to_string();
            if (name == "diffuse")
                ss << diffuseN++;
            else if (name == "specular")
                ss << specularN++;
            else if (name == "reflection")
                ss << specularN++;
            else
            {
                PRINT_ERROR("Unsupported texture type provided. Skipping.");
                continue;
            }
            number = ss.str();

            glUniform1i(glGetUniformLocation(shader._program, ("material." + name + number).c_str()), i + 1);
            glBindTexture(GL_TEXTURE_2D, this->_textures.at(i)->get_id());
        }
        glActiveTexture(GL_TEXTURE1);

        // Draw mesh
        glBindVertexArray(this->_VAO);
        glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    // -----------------
    // Private Functions
    // -----------------

    void Mesh::setup_mesh()
    {
        glGenVertexArrays(1, &this->_VAO);
        glGenBuffers(1, &this->_VBO);
        glGenBuffers(1, &this->_EBO);

        glBindVertexArray(this->_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
        glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(Vertex), &this->_vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_indices.size() * sizeof(GLuint), &this->_indices[0], GL_STATIC_DRAW);

        // Vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) 0);

        // Vertex Normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, _normal));

        // Texture Coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, _tex_coords));

        glBindVertexArray(0);
    }

    Texture* Mesh::texture_from_file(const char* path, std::string directory)
    {
        //Generate texture ID and load texture data
        std::string filename(path);
        filename = directory + "/" + filename;
        return Texture::create(filename);
    }
}
