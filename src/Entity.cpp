#include "Entity.hpp"
#include <iostream>

namespace Larp
{
    Entity::Entity(ModelPtr model)
        : _shader(Shader::get_default_shader()),
        _model(model)
    {
    }

    EntityPtr Entity::create(ModelPtr model)
    {
        return new Entity(model);
    }

    void Entity::draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const glm::vec3& view_pos)
    {
        this->_shader->use();

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
