#pragma once

#include <glm/glm.hpp>

#include "LarpPrerequisites.hpp"

namespace Larp
{
    class PointLight
    {
    private:
    	glm::vec3 _position;

    	const float _constant;

    	float _linear;

    	float _quadratic;

    	glm::vec3 _ambient;

    	glm::vec3 _diffuse;

    	glm::vec3 _specular;

    public:
        PointLight();
        
    	void set_position(glm::vec3 position);

    	void set_position(float x, float y, float z);

        void set_attenutation(float linear, float quadratic);

    	void set_ambient_color(glm::vec3 color);

    	void set_ambient_color(float x, float y, float z);

        void set_diffuse_color(glm::vec3 color);

        void set_diffuse_color(float x, float y, float z);

        void set_specular_color(glm::vec3 color);

        void set_specular_color(float x, float y, float z);
    };
}