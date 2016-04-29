#include "SkyBox.hpp"

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
        add_vertices();

        // Get the shader
        this->_shader = new Shader("shaders/skybox.vert", "shaders/skybox.frag");

        // Setup the VAO
        glGenVertexArrays(1, &this->_VAO);
        glGenBuffers(1, &this->_VBO);

        glBindVertexArray(this->_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
        glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(glm::vec3), &this->_vertices[0], GL_STATIC_DRAW);

        // Vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
        glBindVertexArray(0);

        glGenTextures(1, &this->_texture_id);

        int width, height;
        unsigned char* image;

        glBindTexture(GL_TEXTURE_CUBE_MAP, this->_texture_id);
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
        this->_vertices.push_back(glm::vec3(-1.0f,  1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f, -1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f, -1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f,  1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3(-1.0f,  1.0f, -1.0f));

        this->_vertices.push_back(glm::vec3(-1.0f, -1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3(-1.0f,  1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3(-1.0f,  1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3(-1.0f,  1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3(-1.0f, -1.0f,  1.0f));

        this->_vertices.push_back(glm::vec3( 1.0f, -1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f, -1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f,  1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f,  1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f,  1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f, -1.0f, -1.0f));

        this->_vertices.push_back(glm::vec3(-1.0f, -1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3(-1.0f,  1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f,  1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f,  1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f, -1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3(-1.0f, -1.0f,  1.0f));

        this->_vertices.push_back(glm::vec3(-1.0f,  1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f,  1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f,  1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f,  1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3(-1.0f,  1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3(-1.0f,  1.0f, -1.0f));

        this->_vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3(-1.0f, -1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f, -1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f, -1.0f, -1.0f));
        this->_vertices.push_back(glm::vec3(-1.0f, -1.0f,  1.0f));
        this->_vertices.push_back(glm::vec3( 1.0f, -1.0f,  1.0f));
    }

    void SkyBox::draw(const glm::mat4& view, const glm::mat4& projection)
    {
        glDepthMask(GL_FALSE);
        this->_shader->use();
        // Remove translation part of the view matrix
        glm::mat4 new_view = glm::mat4(glm::mat3(view));
        glUniformMatrix4fv(glGetUniformLocation(this->_shader->_program, "projection"),
                           1,
                           GL_FALSE,
                           glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(this->_shader->_program, "view"),
                           1,
                           GL_FALSE,
                           glm::value_ptr(new_view));
        glBindVertexArray(this->_VAO);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(this->_shader->_program, "skybox"), 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->_texture_id);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthMask(GL_TRUE);
    }
}
