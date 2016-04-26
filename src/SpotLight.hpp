#pragma once

#include <glm/glm.hpp>

#include "LarpPrerequisites.hpp"

namespace Larp
{
    class SpotLight
    {
    private:
    	glm::vec3 _position;

    	glm::vec3 _direction;

    	GLfloat _cut_off;

    	GLfloat _outer_cut_off;

    	const GLfloat _constant;

    	GLfloat _linear;

    	GLfloat _quadratic;

    	glm::vec3 _ambient;

    	glm::vec3 _diffuse;

    	glm::vec3 _specular;
    public:
        SpotLight();

    	void set_position(glm::vec3 position);

    	void set_position(GLfloat x, GLfloat y, GLfloat z);

    	void set_direction(glm::vec3 direction);

        void set_direction(GLfloat x, GLfloat y, GLfloat z);

        void set_inner_radius(GLfloat radius);

        void set_outer_radius(GLfloat radius);

    	void set_attenutation(GLfloat linear, GLfloat quadratic);

    	void set_ambient_color(glm::vec3 color);

    	void set_ambient_color(GLfloat x, GLfloat y, GLfloat z);

        void set_diffuse_color(glm::vec3 color);

        void set_diffuse_color(GLfloat x, GLfloat y, GLfloat z);

        void set_specular_color(glm::vec3 color);

        void set_specular_color(GLfloat x, GLfloat y, GLfloat z);
    };
}