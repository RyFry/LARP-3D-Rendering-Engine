#include "Mesh.hpp"

namespace Larp
{
    // -------
    // Texture
    // -------

    std::string Texture::toString()
    {
        if (this->mType == Texture::DIFFUSE)
            return "texture_diffuse";
        if (this->mType == Texture::SPECULAR)
            return "texture_specular";
        return "";
    }

    // ----------------
    // Public Functions
    // ----------------

    Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures) :
        vertices(vertices),
        indices(indices),
        textures(textures)
    {
        this->setupMesh();
    }

    void Mesh::draw(Shader& shader)
    {
        GLuint diffuseN = 1;
        GLuint specularN = 1;
        for (GLuint i = 0; i < this->textures.size(); ++i)
        {
            glActiveTexture(GL_TEXTURE0 + i); // Activate the proper texture unit before binding
            // Retrieve the texture number (texture_diffuseN or texture_specularN)
            std::stringstream ss;
            std::string number;
            std::string name = this->textures.at(i).toString();
            if (name == "texture_diffuse")
                ss << diffuseN++;
            else if (name == "texture_specular")
                ss << specularN++;
            number = ss.str();

            glUniform1f(glGetUniformLocation(shader._program, ("material." + name + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, this->textures.at(i).mID);
        }
        glActiveTexture(GL_TEXTURE0);

        // Draw mesh
        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }


    // -----------------
    // Private Functions
    // -----------------

    void Mesh::setupMesh()
    {
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

        // Vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) 0);

        // Vertex Normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, mNormal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, mTexCoords));

        glBindVertexArray(0);
    }
}
