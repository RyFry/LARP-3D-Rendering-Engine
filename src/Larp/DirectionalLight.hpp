#pragma once

#include <glm/glm.hpp>

#include "LarpPrerequisites.hpp"

namespace Larp
{
    struct DirectionalLight
    {
        /**
         * The direction the DirectionalLight is aiming
         */
        glm::vec3 m_direction;
        /**
         * Intensity of this DirectionalLight's ambient light. Ambient light is usually set to
         * a low intensity because the ambient color should not be too dominant.
         */
        glm::vec3 m_ambient;
        /**
         * Intensity of this DirectionalLight's diffuse light. Diffuse light is usually set to
         * to the exact color the user would like the light to have; often a bright white
         * color.
         */
        glm::vec3 m_diffuse;
        /**
         * Intensity of this DirectionalLight's specular light. Specular light is usually kept at
         * glm::vec3(1.0f) shining at full intensity.
         */
        glm::vec3 m_specular;
        /**
         * Constructor
         * @param x The x value of the DirectionalLight's direction.
         * @param y The y value of the DirectionalLight's direction.
         * @param z The z value of the DirectionalLight's direction.
         */
        DirectionalLight(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Sets the direction the DirectionalLight is pointing in
         * @param direction The new direction of this light.
         */
        void set_direction(glm::vec3 direction);
        /**
         * Sets the direction the DirectionalLight is pointing in
         * @param x The new x direction.
         * @param x The new y direction.
         * @param x The new z direction.
         */
        void set_direction(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Sets the ambient intensity of the DirectionalLight
         * @param intensity The new intensity of this light.
         */
        void set_ambient_intensity(glm::vec3 intensity);
        /**
         * Sets the ambient intensity of the DirectionalLight
         * @param x The new x intensity.
         * @param x The new y intensity.
         * @param x The new z intensity.
         */
        void set_ambient_intensity(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Sets the diffuse intensity of the DirectionalLight
         * @param intensity The new intensity of this light.
         */
        void set_diffuse_intensity(glm::vec3 intensity);
        /**
         * Sets the diffuse intensity of the DirectionalLight
         * @param x The new x intensity.
         * @param x The new y intensity.
         * @param x The new z intensity.
         */
        void set_diffuse_intensity(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Sets the specular intensity of the DirectionalLight
         * @param intensity The new intensity of this light.
         */
        void set_specular_intensity(glm::vec3 intensity);
        /**
         * Sets the specular intensity of the DirectionalLight
         * @param x The new x intensity.
         * @param x The new y intensity.
         * @param x The new z intensity.
         */
        void set_specular_intensity(GLfloat x, GLfloat y, GLfloat z);
    };
}
