#include "Entity.hpp"
#include <iostream>

namespace Larp
{
    Entity::Entity(const Shader& shader, ModelPtr model)
        : _shader(shader),
          _model(model)
    {}

    EntityPtr Entity::create(const Shader& shader, ModelPtr model)
    {
        return new Entity(shader, model);
    }

    void Entity::draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
    {
        this->_shader.use();

        glUniformMatrix4fv(glGetUniformLocation(this->_shader._program, "projection"), 1, GL_FALSE,
                           glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(this->_shader._program, "view"), 1, GL_FALSE,
                           glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(this->_shader._program, "model"), 1, GL_FALSE,
                           glm::value_ptr(model));

        this->_model->draw(this->_shader);
    }
}
