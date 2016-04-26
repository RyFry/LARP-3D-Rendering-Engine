#include "SpotLight.hpp"
namespace Larp
{
    const GLfloat _constant = 1.0f;

    SpotLight::SpotLight(GLfloat x, GLfloat y, GLfloat z)
        : _position(glm::vec3(x, y, z)),
        _cut_off(12.5f),
        _outer_cut_off(15.0f),
        _linear(0.09f),
        _quadratic(0.032f),
        _diffuse(glm::vec3(1.0f)),
        _specular(glm::vec3(1.0f))
    {
    }

    void SpotLight::set_position(glm::vec3 position)
    {
        this->_position = position;
    }

    void SpotLight::set_position(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_position.x = x;
        this->_position.y = y;
        this->_position.z = z;
    }

    void SpotLight::set_direction(glm::vec3 direction)
    {
        this->_direction = direction;
    }

    void SpotLight::set_direction(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_direction.x = x;
        this->_direction.y = y;
        this->_direction.z = z;
    }

    void SpotLight::set_inner_radius(GLfloat radius)
    {
        this->_cut_off = radius;
    }

    void SpotLight::set_outer_radius(GLfloat radius)
    {
        this->_outer_cut_off = radius;
    }

    void SpotLight::set_attenutation(GLfloat linear, GLfloat quadratic)
    {
        this->_linear = linear;
        this->_quadratic = quadratic;
    }

    void SpotLight::set_ambient_intensity(glm::vec3 intensity)
    {
        this->_ambient = intensity; 
    }

    void SpotLight::set_ambient_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_ambient.x = x;
        this->_ambient.y = y;
        this->_ambient.z = z;
    }

    void SpotLight::set_diffuse_intensity(glm::vec3 intensity)
    {
        this->_diffuse = intensity;
    }

    void SpotLight::set_diffuse_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_diffuse.x = x;
        this->_diffuse.y = y;
        this->_diffuse.z = z;
    }

    void SpotLight::set_specular_intensity(glm::vec3 intensity)
    {
        this->_specular = intensity;
    }

    void SpotLight::set_specular_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_specular.x = x;
        this->_specular.y = y;
        this->_specular.z = z;
    }
}
