#include "Mesh.hpp"

namespace Larp
{
    // -------
    // Texture
    // -------

    std::string Texture::to_string()
    {
        if (this->_type == Texture::DIFFUSE)
            return "diffuse";
        if (this->_type == Texture::SPECULAR)
            return "specular";
        return "";
    }

    // ----------------
    // Public Functions
    // ----------------

    Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures) :
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
        for (GLuint i = 0; i < this->_textures.size(); ++i)
        {
            glActiveTexture(GL_TEXTURE0 + i); // Activate the proper texture unit before binding
            // Retrieve the texture number (diffuseN or specularN)
            std::stringstream ss;
            std::string number;
            std::string name = this->_textures.at(i).to_string();
            if (name == "diffuse")
                ss << diffuseN++;
            else if (name == "specular")
                ss << specularN++;
            else
            {
                PRINT_ERROR("Unsupported texture type provided. Skipping.");
                continue;
            }
            number = ss.str();

            glUniform1i(glGetUniformLocation(shader._program, ("material." + name + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, this->_textures.at(i)._id);
        }
        glActiveTexture(GL_TEXTURE0);

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

    GLint Mesh::texture_from_file(const char* path, std::string directory)
    {
        //Generate texture ID and load texture data
        std::string filename(path);
        filename = directory + "/" + filename;
        GLuint textureID;
        glGenTextures(1, &textureID);
        int width, height;
        unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
        // Assign texture to ID
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Parameters
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        SOIL_free_image_data(image);
        return textureID;
    }
}
