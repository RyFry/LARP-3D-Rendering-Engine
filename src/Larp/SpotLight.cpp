#include "SpotLight.hpp"
namespace Larp
{
    const GLfloat SpotLight::sc_constant = 1.0f;

    SpotLight::SpotLight(GLfloat x, GLfloat y, GLfloat z)
        : m_position(glm::vec3(x, y, z)),
        m_cut_off(12.5f),
        m_outer_cut_off(15.0f),
        m_linear(0.09f),
        m_quadratic(0.032f),
        m_diffuse(glm::vec3(1.0f)),
        m_specular(glm::vec3(1.0f))
    {
    }

    void SpotLight::set_position(glm::vec3 position)
    {
        m_position = position;
    }

    void SpotLight::set_position(GLfloat x, GLfloat y, GLfloat z)
    {
        m_position.x = x;
        m_position.y = y;
        m_position.z = z;
    }

    void SpotLight::set_direction(glm::vec3 direction)
    {
        m_direction = direction;
    }

    void SpotLight::set_direction(GLfloat x, GLfloat y, GLfloat z)
    {
        m_direction.x = x;
        m_direction.y = y;
        m_direction.z = z;
    }

    void SpotLight::set_inner_radius(GLfloat radius)
    {
        m_cut_off = radius;
    }

    void SpotLight::set_outer_radius(GLfloat radius)
    {
        m_outer_cut_off = radius;
    }

    void SpotLight::set_attenutation(GLfloat linear, GLfloat quadratic)
    {
        m_linear = linear;
        m_quadratic = quadratic;
    }

    void SpotLight::set_ambient_intensity(glm::vec3 intensity)
    {
        m_ambient = intensity; 
    }

    void SpotLight::set_ambient_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        m_ambient.x = x;
        m_ambient.y = y;
        m_ambient.z = z;
    }

    void SpotLight::set_diffuse_intensity(glm::vec3 intensity)
    {
        m_diffuse = intensity;
    }

    void SpotLight::set_diffuse_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        m_diffuse.x = x;
        m_diffuse.y = y;
        m_diffuse.z = z;
    }

    void SpotLight::set_specular_intensity(glm::vec3 intensity)
    {
        m_specular = intensity;
    }

    void SpotLight::set_specular_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        m_specular.x = x;
        m_specular.y = y;
        m_specular.z = z;
    }
}
