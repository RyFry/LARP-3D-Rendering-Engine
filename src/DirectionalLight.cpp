#include "DirectionalLight.hpp"
namespace Larp
{
    DirectionalLight::DirectionalLight(GLfloat x, GLfloat y, GLfloat z)
        : _direction(glm::vec3(x, y, z)),
        _ambient(glm::vec3(0.15f)),
        _diffuse(glm::vec3(1.0f)),
        _specular(glm::vec3(1.0f))
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
    
    void DirectionalLight::set_ambient_intensity(glm::vec3 intensity)
    {
        this->_ambient = intensity; 
    }

    void DirectionalLight::set_ambient_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_ambient.x = x;
        this->_ambient.y = y;
        this->_ambient.z = z;
    }

    void DirectionalLight::set_diffuse_intensity(glm::vec3 intensity)
    {
        this->_diffuse = intensity;
    }

    void DirectionalLight::set_diffuse_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_diffuse.x = x;
        this->_diffuse.y = y;
        this->_diffuse.z = z;
    }

    void DirectionalLight::set_specular_intensity(glm::vec3 intensity)
    {
        this->_specular = intensity;
    }

    void DirectionalLight::set_specular_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        this->_specular.x = x;
        this->_specular.y = y;
        this->_specular.z = z;
    }
}
