#include "PointLight.hpp"
namespace Larp
{
    PointLight::PointLight()
        : _constant(1.0f),
        _linear(0.09f),
        _quadratic(0.032f),
        _ambient(glm::vec3(0.05f)),
        _diffuse(glm::vec3(0.8f)),
        _specular(glm::vec3(1.0f))
    {
    }

    void PointLight::set_position(glm::vec3 position)
    {
        this->_position = position;
    }

    void PointLight::set_position(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_position.x = x;
        this->_position.y = y;
        this->_position.z = z;
    }

    void PointLight::set_attenutation(GLfloat linear, GLfloat quadratic)
    {
        this->_linear = linear;
        this->_quadratic = quadratic;
    }

    void PointLight::set_ambient_color(glm::vec3 color)
    {
        this->_ambient = color; 
    }

    void PointLight::set_ambient_color(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_ambient.x = x;
        this->_ambient.y = y;
        this->_ambient.z = z;
    }

    void PointLight::set_diffuse_color(glm::vec3 color)
    {
        this->_diffuse = color;
    }

    void PointLight::set_diffuse_color(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_diffuse.x = x;
        this->_diffuse.y = y;
        this->_diffuse.z = z;
    }

    void PointLight::set_specular_color(glm::vec3 color)
    {
        this->_specular = color;
    }

    void PointLight::set_specular_color(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_specular.x = x;
        this->_specular.y = y;
        this->_specular.z = z;
    }
}
