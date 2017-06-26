#include "Entity.hpp"
#include <iostream>

namespace Larp
{
    Entity::Entity(Model* model)
        : m_shadow_shader(nullptr),
        m_shader(Shader::get_default_shader()),
        m_model(model)
    {
    }

    Entity* Entity::create(Model* model)
    {
        return new Entity(model);
    }

    void Entity::draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const glm::vec3& view_pos)
    {
        // If not shadows or NOT
        m_shader->use();
        // If shadows
        if (m_shadow_shader)
        {
            // Set light uniforms
            m_shader->set_light_space_matrix(Shader::s_light_space_matrix);
            m_shader->set_dir_light_position(); // not created
            // need depth map texture function
            m_shader->enable_shadow_texture();
        }

        // NOT SHADOWS
        // when is this optional?
        m_shader->set_view_position(view_pos);

        // if specular
        m_shader->set_shininess(32.0f);

        // if directional light is being used
        m_shader->set_directional_lights();

        // if point lighting is enabled
        m_shader->set_point_lights();

        // Spot lights
        // ...

        m_shader->set_mvp(model, view, projection);

        m_model->draw(*m_shader);
    }

    void Entity::draw_shadows(const glm::mat4& model)
    {
        if (m_shadow_shader)
        {
            glUniformMatrix4fv(glGetUniformLocation(m_shadow_shader->m_program, "model"), 1, GL_FALSE,
                           glm::value_ptr(model));
            m_model->draw(*m_shadow_shader); // draw onto the frame buffer
        }
    }

    GLfloat Entity::get_width() const
    {
        return m_model->get_width();
    }

    GLfloat Entity::get_height() const
    {
        return m_model->get_height();
    }

    GLfloat Entity::get_depth() const
    {
        return m_model->get_depth();
    }

    void Entity::set_directional_shadows(bool use_shadow_maps)
    {
        if (use_shadow_maps)
        {
            m_shadow_shader = Shader::get_depth_map_shader();
            m_shader = Shader::get_shadow_map_shader();
        }
        else
        {
            m_shadow_shader = nullptr;
            m_shader = Shader::get_default_shader();
        }
    }

    void Entity::switch_model(Model* m)
    {
        m_model = m;
    }
}
