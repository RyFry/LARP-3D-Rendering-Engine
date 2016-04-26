#pragma once

#include <glm/glm.hpp>

#include "LarpPrerequisites.hpp"

namespace Larp
{
    class DirectionalLight
    {
    private:
    public:
        glm::vec3 _direction;

        glm::vec3 _ambient;

        glm::vec3 _diffuse;

        glm::vec3 _specular;

        DirectionalLight();

        DirectionalLight(GLfloat x, GLfloat y, GLfloat z);

    	void set_direction(glm::vec3 direction);

        void set_direction(GLfloat x, GLfloat y, GLfloat z);

    	void set_ambient_color(glm::vec3 color);

        void set_ambient_color(GLfloat x, GLfloat y, GLfloat z);

        void set_diffuse_color(glm::vec3 color);

        void set_diffuse_color(GLfloat x, GLfloat y, GLfloat z);

        void set_specular_color(glm::vec3 color);

        void set_specular_color(GLfloat x, GLfloat y, GLfloat z);
    };
}