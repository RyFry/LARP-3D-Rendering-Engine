#pragma once

#include <glm/glm.hpp>

#include "LarpPrerequisites.hpp"

namespace Larp
{
    struct SpotLight
    {
        /**
         * This SpotLights's position
         */
        glm::vec3 m_position;
        /**
         * The direction the SpotLight is aiming
         */
        glm::vec3 m_direction;
        /**
         * The inner radius of the SpotLight
         */
        GLfloat m_cut_off;
        /**
         * The outer radius of the SpotLight in which the light gradually dims
         */
        GLfloat m_outer_cut_off;
        /**
         * A constant value used to reduce the SpotLight's intensity over a distance.
         * This is usually kept at 1.0 to make sure the denominator of the equation
         * this value is used in is never smaller than 1.
         */
        static const GLfloat sc_constant;
        /**
         * This linear term is used as part of the attenuation equation which reduces
         * a light's intensity of a distance.
         */
        GLfloat m_linear;
        /**
         * This quadratic term is used as part of the attenuation equation which reduces
         * a light's intensity of a distance.
         */
        GLfloat m_quadratic;
        /**
         * Intensity of this SpotLight's ambient light. Ambient light is usually set to
         * a low intensity because the ambient color should not be too dominant.
         */
        glm::vec3 m_ambient;
        /**
         * Intensity of this SpotLight's diffuse light. Diffuse light is usually set to
         * to the exact color the user would like the light to have; often a bright white
         * color.
         */
        glm::vec3 m_diffuse;
        /**
         * Intensity of this SpotLight's specular light. Specular light is usually kept at
         * glm::vec3(1.0f) shining at full intensity.
         */
        glm::vec3 m_specular;
        /**
         * Constructor
         * @param x The x value of the SpotLight's position.
         * @param y The y value of the SpotLight's position.
         * @param z The z value of the SpotLight's position.
         */
        SpotLight(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Sets the position of the SpotLight
         * @param position The new position of this light.
         */
    	void set_position(glm::vec3 position);
        /**
         * Sets the position of the SpotLight
         * @param x The new x position.
         * @param x The new y position.
         * @param x The new z position.
         */
    	void set_position(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Sets the direction the SpotLight is pointing in
         * @param direction The new direction of this light.
         */
    	void set_direction(glm::vec3 direction);
        /**
         * Sets the direction the SpotLight is pointing in
         * @param x The new x direction.
         * @param x The new y direction.
         * @param x The new z direction.
         */
        void set_direction(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Sets the inner radius of the SpotLight
         * @param radius The new inner radius of this light.
         */
        void set_inner_radius(GLfloat radius);
        /**
         * Sets the outer radius of the SpotLight
         * @param radius The new outer radius of this light.
         */
        void set_outer_radius(GLfloat radius);
        /**
         * Sets the linear and quadratic factors used in this SpotLight's
         * attenutation calculation.
         * @param linear The new linear factor of this light.
         * @param quadratic The new quadratic factor of this light.
         * @note Attenutation reduces the intensity of a light, over the distance a light
         *       ray travels. Setting the right values depends on many factors such as the 
         *       environment, distance the light should cover, and they type of light. Below
         *       there are some good starting points for most lights:
         * @table
         * | Distance | Linear | Quadratic |
         * ---------------------------------
         * | 7        | 0.7    | 1.8       |
         * ---------------------------------
         * | 13       | 0.35   | 0.44      |
         * ---------------------------------
         * | 20       | 0.22   | 0.20      |
         * ---------------------------------
         * | 32       | 0.14   | 0.07      |
         * ---------------------------------
         * | 50       | 0.09   | 0.032     |
         * ---------------------------------
         * | 65       | 0.07   | 0.017     |
         * ---------------------------------
         * | 100      | 0.045  | 0.0075    |
         * ---------------------------------
         * | 160      | 0.027  | 0.0028    |
         * ---------------------------------
         * | 200      | 0.022  | 0.0019    |
         * ---------------------------------
         * | 325      | 0.014  | 0.0007    |
         * ---------------------------------
         * | 600      | 0.007  | 0.0002    |
         * ---------------------------------
         * | 3250     | 0.0014 | 0.000007  |
         * @endtable
         */
    	void set_attenutation(GLfloat linear, GLfloat quadratic);
        /**
         * Sets the ambient intensity of the SpotLight
         * @param intensity The new intensity of this light.
         */
    	void set_ambient_intensity(glm::vec3 intensity);
        /**
         * Sets the ambient intensity of the SpotLight
         * @param x The new x intensity.
         * @param x The new y intensity.
         * @param x The new z intensity.
         */
    	void set_ambient_intensity(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Sets the diffuse intensity of the SpotLight
         * @param intensity The new intensity of this light.
         */
        void set_diffuse_intensity(glm::vec3 intensity);
        /**
         * Sets the diffuse intensity of the SpotLight
         * @param x The new x intensity.
         * @param x The new y intensity.
         * @param x The new z intensity.
         */
        void set_diffuse_intensity(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Sets the specular intensity of the SpotLight
         * @param intensity The new intensity of this light.
         */
        void set_specular_intensity(glm::vec3 intensity);
        /**
         * Sets the specular intensity of the SpotLight
         * @param x The new x intensity.
         * @param x The new y intensity.
         * @param x The new z intensity.
         */
        void set_specular_intensity(GLfloat x, GLfloat y, GLfloat z);
    };
}
