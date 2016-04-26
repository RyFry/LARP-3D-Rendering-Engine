#pragma once

#include <glm/glm.hpp>

#include "LarpPrerequisites.hpp"

namespace Larp
{
    class DirectionalLight
    {
    private:
    	glm::vec3 _direction;

    	glm::vec3 _ambient;

    	glm::vec3 _diffuse;

    	glm::vec3 _specular;

    public:
        DirectionalLight();

    	void set_direction(glm::vec3 direction);

        void set_direction(float x, float y, float z);

    	void set_ambient_color(glm::vec3 color);

        void set_ambient_color(float x, float y, float z);

        void set_diffuse_color(glm::vec3 color);

        void set_diffuse_color(float x, float y, float z);

        void set_specular_color(glm::vec3 color);

        void set_specular_color(float x, float y, float z);
    };
}