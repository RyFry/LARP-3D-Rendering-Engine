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

    void Entity::draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection,
                      const glm::vec3& view_pos,
                      const std::vector<UniqueDirectional>& directional_lights,
                      const std::vector<UniquePoint>& point_lights,
                      const std::vector<UniqueSpot>& spot_lights)
    {
        this->_shader.use();

        glUniform3f(glGetUniformLocation(this->_shader._program, "viewPos"), view_pos.x, view_pos.y, view_pos.z);
        glUniform1f(glGetUniformLocation(this->_shader._program, "material.shininess"), 32.0f);

        bool use_directional_lighting = !directional_lights.empty();
        glUniform1i(glGetUniformLocation(this->_shader._program, "directionalLight"), use_directional_lighting);

        // Directional light
        if (use_directional_lighting)
        {
          // std::cout << "dir light" << std::endl;
          glUniform3f(glGetUniformLocation(this->_shader._program, "dirLight.direction"), directional_lights[0]->_direction.x, directional_lights[0]->_direction.y, directional_lights[0]->_direction.z);
          glUniform3f(glGetUniformLocation(this->_shader._program, "dirLight.ambient"), directional_lights[0]->_ambient.x, directional_lights[0]->_ambient.y, directional_lights[0]->_ambient.z);
          glUniform3f(glGetUniformLocation(this->_shader._program, "dirLight.diffuse"), directional_lights[0]->_diffuse.x, directional_lights[0]->_diffuse.y, directional_lights[0]->_diffuse.z);
          glUniform3f(glGetUniformLocation(this->_shader._program, "dirLight.specular"), directional_lights[0]->_specular.x, directional_lights[0]->_specular.y, directional_lights[0]->_specular.z);
        }

        int num_point_lights = point_lights.size();
        glUniform1i(glGetUniformLocation(this->_shader._program, "numPointLights"), num_point_lights);
        
        // Point lights
        for (int i = 0; i < num_point_lights; ++i)
        {
          glUniform3f(glGetUniformLocation(this->_shader._program, ("pointLights[" + std::to_string(i) + "].position").c_str()), point_lights[i]->_position.x, point_lights[i]->_position.y, point_lights[i]->_position.z);
          glUniform3f(glGetUniformLocation(this->_shader._program, ("pointLights[" + std::to_string(i) + "].ambient").c_str()), point_lights[i]->_ambient.x, point_lights[i]->_ambient.y, point_lights[i]->_ambient.z);
          glUniform3f(glGetUniformLocation(this->_shader._program, ("pointLights[" + std::to_string(i) + "].diffuse").c_str()), point_lights[i]->_diffuse.x, point_lights[i]->_diffuse.y, point_lights[i]->_diffuse.z);
          glUniform3f(glGetUniformLocation(this->_shader._program, ("pointLights[" + std::to_string(i) + "].specular").c_str()), point_lights[i]->_specular.x, point_lights[i]->_specular.y, point_lights[i]->_specular.z);
          glUniform1f(glGetUniformLocation(this->_shader._program, ("pointLights[" + std::to_string(i) + "].constant").c_str()), point_lights[i]->_constant);
          glUniform1f(glGetUniformLocation(this->_shader._program, ("pointLights[" + std::to_string(i) + "].linear").c_str()), point_lights[i]->_linear);
          glUniform1f(glGetUniformLocation(this->_shader._program, ("pointLights[" + std::to_string(i) + "].quadratic").c_str()), point_lights[i]->_quadratic);
        }
        // Spot lights
        // ...

        glUniformMatrix4fv(glGetUniformLocation(this->_shader._program, "projection"), 1, GL_FALSE,
                           glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(this->_shader._program, "view"), 1, GL_FALSE,
                           glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(this->_shader._program, "model"), 1, GL_FALSE,
                           glm::value_ptr(model));

        this->_model->draw(this->_shader);
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
}
