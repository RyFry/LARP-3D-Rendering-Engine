#include "DirectionalLight.hpp"
namespace Larp
{
    DirectionalLight::DirectionalLight()
        : _direction(glm::vec3(-0.2f, -1.0f, -0.3f)),
        _ambient(glm::vec3(0.05f)),
        _diffuse(glm::vec3(0.4f)),
        _specular(glm::vec3(0.5f))
    {
    }

    void DirectionalLight::set_direction(glm::vec3 direction)
    {
        this->_direction = direction;
    }

    void DirectionalLight::set_direction(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_direction.x = x;
        this->_direction.y = y;
        this->_direction.z = z;
    }
    
    void DirectionalLight::set_ambient_color(glm::vec3 color)
    {
        this->_ambient = color; 
    }

    void DirectionalLight::set_ambient_color(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_ambient.x = x;
        this->_ambient.y = y;
        this->_ambient.z = z;
    }

    void DirectionalLight::set_diffuse_color(glm::vec3 color)
    {
        this->_diffuse = color;
    }

    void DirectionalLight::set_diffuse_color(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_diffuse.x = x;
        this->_diffuse.y = y;
        this->_diffuse.z = z;
    }

    void DirectionalLight::set_specular_color(glm::vec3 color)
    {
        this->_specular = color;
    }

    void DirectionalLight::set_specular_color(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_specular.x = x;
        this->_specular.y = y;
        this->_specular.z = z;
    }
}
