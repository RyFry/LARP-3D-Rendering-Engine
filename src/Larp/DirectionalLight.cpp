#include "DirectionalLight.hpp"
namespace Larp
{
    DirectionalLight::DirectionalLight(GLfloat x, GLfloat y, GLfloat z)
        : m_direction(glm::vec3(x, y, z)),
          m_ambient(glm::vec3(0.05f)),
          m_diffuse(glm::vec3(0.4f)),
          m_specular(glm::vec3(0.5f))
    {
    }

    void DirectionalLight::set_direction(glm::vec3 direction)
    {
        m_direction = direction;
    }

    void DirectionalLight::set_direction(GLfloat x, GLfloat y, GLfloat z)
    {
        m_direction.x = x;
        m_direction.y = y;
        m_direction.z = z;
    }

    void DirectionalLight::set_ambient_intensity(glm::vec3 intensity)
    {
        m_ambient = intensity;
    }

    void DirectionalLight::set_ambient_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        m_ambient.x = x;
        m_ambient.y = y;
        m_ambient.z = z;
    }

    void DirectionalLight::set_diffuse_intensity(glm::vec3 intensity)
    {
        m_diffuse = intensity;
    }

    void DirectionalLight::set_diffuse_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        m_diffuse.x = x;
        m_diffuse.y = y;
        m_diffuse.z = z;
    }

    void DirectionalLight::set_specular_intensity(glm::vec3 intensity)
    {
        m_specular = intensity;
    }

    void DirectionalLight::set_specular_intensity(GLfloat x, GLfloat y, GLfloat z)
    {
        m_specular.x = x;
        m_specular.y = y;
        m_specular.z = z;
    }
}
