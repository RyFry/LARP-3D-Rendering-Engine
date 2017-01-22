#include "SkyBox.hpp"

// Macro for adding verts to the sky box
#define ADD_VERT(X, Y, Z) (m_vertices.push_back(glm::vec3(X, Y, Z)));

namespace Larp
{
    SkyBox::SkyBox(std::string pos_x, std::string neg_x,
                   std::string pos_y, std::string neg_y,
                   std::string pos_z, std::string neg_z)
    {
        std::vector<const GLchar*> faces;
        faces.push_back(pos_x.c_str());
        faces.push_back(neg_x.c_str());
        faces.push_back(pos_y.c_str());
        faces.push_back(neg_y.c_str());
        faces.push_back(pos_z.c_str());
        faces.push_back(neg_z.c_str());
        this->setup_skybox(faces);
    }

    SkyBox::SkyBox(std::vector<const GLchar*> faces)
    {
        if (faces.size() < 6)
        {
            THROW_RUNTIME_ERROR("Cannot create a SkyBox without 6 faces");
        }
        this->setup_skybox(faces);
    }

    void SkyBox::setup_skybox(std::vector<const GLchar*> faces)
    {
        this->add_vertices();

        // Get the shader
        m_shader = Shader::get_skybox_shader();

        // Setup the VAO
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);

        // Vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
        glBindVertexArray(0);

        glGenTextures(1, &m_texture_id);

        int width, height;
        unsigned char* image;

        glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);
        for(GLuint i = 0; i < faces.size(); ++i)
        {
            image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
                GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
                );
            SOIL_free_image_data(image);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void SkyBox::add_vertices()
    {
        ADD_VERT(-1.0f,  1.0f, -1.0f)
        ADD_VERT(-1.0f, -1.0f, -1.0f)
        ADD_VERT( 1.0f, -1.0f, -1.0f)
        ADD_VERT( 1.0f, -1.0f, -1.0f)
        ADD_VERT( 1.0f,  1.0f, -1.0f)
        ADD_VERT(-1.0f,  1.0f, -1.0f)

        ADD_VERT(-1.0f, -1.0f,  1.0f)
        ADD_VERT(-1.0f, -1.0f, -1.0f)
        ADD_VERT(-1.0f,  1.0f, -1.0f)
        ADD_VERT(-1.0f,  1.0f, -1.0f)
        ADD_VERT(-1.0f,  1.0f,  1.0f)
        ADD_VERT(-1.0f, -1.0f,  1.0f)

        ADD_VERT( 1.0f, -1.0f, -1.0f)
        ADD_VERT( 1.0f, -1.0f,  1.0f)
        ADD_VERT( 1.0f,  1.0f,  1.0f)
        ADD_VERT( 1.0f,  1.0f,  1.0f)
        ADD_VERT( 1.0f,  1.0f, -1.0f)
        ADD_VERT( 1.0f, -1.0f, -1.0f)

        ADD_VERT(-1.0f, -1.0f,  1.0f)
        ADD_VERT(-1.0f,  1.0f,  1.0f)
        ADD_VERT( 1.0f,  1.0f,  1.0f)
        ADD_VERT( 1.0f,  1.0f,  1.0f)
        ADD_VERT( 1.0f, -1.0f,  1.0f)
        ADD_VERT(-1.0f, -1.0f,  1.0f)

        ADD_VERT(-1.0f,  1.0f, -1.0f)
        ADD_VERT( 1.0f,  1.0f, -1.0f)
        ADD_VERT( 1.0f,  1.0f,  1.0f)
        ADD_VERT( 1.0f,  1.0f,  1.0f)
        ADD_VERT(-1.0f,  1.0f,  1.0f)
        ADD_VERT(-1.0f,  1.0f, -1.0f)

        ADD_VERT(-1.0f, -1.0f, -1.0f)
        ADD_VERT(-1.0f, -1.0f,  1.0f)
        ADD_VERT( 1.0f, -1.0f, -1.0f)
        ADD_VERT( 1.0f, -1.0f, -1.0f)
        ADD_VERT(-1.0f, -1.0f,  1.0f)
        ADD_VERT( 1.0f, -1.0f,  1.0f)
    }

    void SkyBox::draw(const glm::mat4& view, const glm::mat4& projection)
    {
        glDepthFunc(GL_LEQUAL);
        m_shader->use();
        // Remove translation part of the view matrix
        glm::mat4 new_view = glm::mat4(glm::mat3(view));
        glUniformMatrix4fv(glGetUniformLocation(m_shader->m_program, "projection"),
                           1,
                           GL_FALSE,
                           glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(m_shader->m_program, "view"),
                           1,
                           GL_FALSE,
                           glm::value_ptr(new_view));
        glBindVertexArray(m_VAO);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(m_shader->m_program, "skybox"), 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
    }
}
