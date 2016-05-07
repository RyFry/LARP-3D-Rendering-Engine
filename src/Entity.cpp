#include "Entity.hpp"
#include <iostream>

namespace Larp
{
    Entity::Entity(ModelPtr model)
        : _shadow_shader(nullptr),
        _shader(Shader::get_default_shader()),
        _model(model)
    {
    }

    EntityPtr Entity::create(ModelPtr model)
    {
        return new Entity(model);
    }

    void Entity::draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const glm::vec3& view_pos)
    {
        glm::mat4 light_space_matrix;
        // If shadows
        if (_shadow_shader)
        {
            this->_shadow_shader->use();
            light_space_matrix = this->_shadow_shader->calculate_light_space_matrix();
            // - now render scene from light's point of view
            this->_shadow_shader->set_light_space_matrix(light_space_matrix);
            this->_shadow_shader->prepare_depth_map();

            glUniformMatrix4fv(glGetUniformLocation(this->_shadow_shader->_program, "model"), 1, GL_FALSE,
                           glm::value_ptr(model));

            this->_model->draw(*_shadow_shader); // draw onto the frame buffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // ... draw the actual scene...
        }

        // If not shadows or NOT
        this->_shader->use();
        // If shadows
        if (_shadow_shader)
        {
            // move this into a function
            Larp::ConfigurationLoader config("larp.cfg");
            glViewport(0, 0, config.get_width(), config.get_height()); // need to make these values a variable, possibly in larp prereqs
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // Set light uniforms
            this->_shader->set_light_space_matrix(light_space_matrix);
            this->_shader->set_dir_light_position(); // not created
            // need depth map texture function
            this->_shader->enable_shadow_texture();
        }

        // NOT SHADOWS
        // when is this optional?
        this->_shader->set_view_position(view_pos);

        // if specular
        this->_shader->set_shininess(32.0f);

        // if directional light is being used
        this->_shader->set_directional_lights();

        // if point lighting is enabled
        this->_shader->set_point_lights();

        // Spot lights
        // ...

        this->_shader->set_mvp(model, view, projection);

        this->_model->draw(*_shader);
    }

    GLfloat Entity::get_width() const
    {
        return this->_model->get_width();
    }

    GLfloat Entity::get_height() const
    {
        return this->_model->get_height();
    }

    GLfloat Entity::get_depth() const
    {
        return this->_model->get_depth();
    }

    void Entity::set_directional_shadows(bool value)
    {
        if (value)
        {
            this->_shadow_shader = Shader::get_depth_map_shader();
            this->_shader = Shader::get_shadow_map_shader();
        }
        else
        {
            this->_shadow_shader = nullptr;
            this->_shader = Shader::get_default_shader();
        }
    }
}
