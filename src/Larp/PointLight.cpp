#include "PointLight.hpp"
namespace Larp
{
    const GLfloat PointLight::sc_constant = 1.0f;

    PointLight::PointLight(GLfloat x, GLfloat y, GLfloat z)
        : m_position(glm::vec3(x, y, z)),
        m_linear(0.09f),
        m_quadratic(0.032f),
        m_ambient(glm::vec3(0.05f)),
        m_diffuse(glm::vec3(0.8f)),
        m_specular(glm::vec3(1.0f))
    {
    }

    void PointLight::set_position(glm::vec3 position)
    {
        m_position = position;
    }

    void PointLight::set_position(GLfloat x, GLfloat y, GLfloat z)
    {
        m_position.x = x;
        m_position.y = y;
        m_position.z = z;
    }

    void PointLight::set_attenutation(GLfloat linear, GLfloat quadratic)
    {
        m_linear = linear;
        m_quadratic = quadratic;
    }

    void PointLight::set_ambient_intensity(glm::vec3 intensity)
    {
        m_ambient = intensity; 
    }

    void PointLight::set_ambient_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        m_ambient.x = x;
        m_ambient.y = y;
        m_ambient.z = z;
    }

    void PointLight::set_diffuse_intensity(glm::vec3 intensity)
    {
        m_diffuse = intensity;
    }

    void PointLight::set_diffuse_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        m_diffuse.x = x;
        m_diffuse.y = y;
        m_diffuse.z = z;
    }

    void PointLight::set_specular_intensity(glm::vec3 intensity)
    {
        m_specular = intensity;
    }

    void PointLight::set_specular_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        m_specular.x = x;
        m_specular.y = y;
        m_specular.z = z;
    }
}
