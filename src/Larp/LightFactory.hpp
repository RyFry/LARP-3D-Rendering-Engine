#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Larp/LarpPrerequisites.hpp"
#include "Larp/Mesh.hpp"

#include "Larp/DirectionalLight.hpp"
#include "Larp/PointLight.hpp"
#include "Larp/SpotLight.hpp"

namespace Larp
{
    class LightFactory
    {
    private:
        /**
         * This is the maximum number of directional lights that may be added to the SceneGraph
         */
        static const size_t sc_max_directional_lights;
        /**
         * This is the maximum number of point lights that may be added to the SceneGraph
         */
        static const size_t sc_max_point_lights;
        /**
         * This is the maximum number of spot lights that may be added to the SceneGraph
         * @warning SpotLights are not currently supported.
         */
        static const size_t sc_max_spot_lights;
    public:
        /**
         * The vector of directional lights currently held by the SceneGraph.
         * If the vector is not empty, these will eventually be incorporated 
         * in the lighting calculations after they are passed from the SceneGraph
         * to the Node(s) and eventually and Entity.
         */
        static std::vector<UniqueDirectional> s_directional_lights;
        /**
         * The vector of point lights currently held by the SceneGraph.
         * If the vector is not empty, these will eventually be incorporated 
         * in the lighting calculations after they are passed from the SceneGraph
         * to the Node(s) and eventually and Entity.
         */
        static std::vector<UniquePoint> s_point_lights;
        /**
         * The vector of spot lights currently held by the SceneGraph.
         * If the vector is not empty, these will eventually be incorporated 
         * in the lighting calculations after they are passed from the SceneGraph
         * to the Node(s) and eventually and Entity.
         */
        static std::vector<UniqueSpot> s_spot_lights;
        /**
         * Creates a directional light that faces downwards by default and adds the light
         * to the SceneGraph's vector of directional lights.
         * @param direction The direction the light should be facing.
         * @returns Returns a const DirectionalLight pointer that may be used to change
         *          lighting parameters.
         * @warning Do not add this type of light if Entity specified shaders do not support them.
         */
        static DirectionalLight* create_directional_light(glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f));
        /**
         * Creates a directional light that faces downwards by default and adds the light
         * to the SceneGraph's vector of directional lights.
         * @param x The x direction the light should be facing.
         * @param y The y direction the light should be facing.
         * @param z The z direction the light should be facing.
         * @returns Returns a const DirectionalLight pointer that may be used to change
         *          lighting parameters.
         * @warning Do not add this type of light if Entity specified shaders do not support them.
         */
        static DirectionalLight* create_directional_light(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Creates a point light that is positioned at (0, 0, 0) by default and adds the light
         * to the SceneGraph's vector of point lights.
         * @param position The starting position of the light.
         * @returns Returns a const PointLight pointer that may be used to change
         *          lighting parameters.
         * @warning Do not add this type of light if Entity specified shaders do not support them.
         */
        static PointLight* create_point_light(glm::vec3 position = glm::vec3(0.0f));
        /**
         * Creates a point light that is positioned at (0, 0, 0) by default and adds the light
         * to the SceneGraph's vector of point lights.
         * @param position The starting position of the light.
         * @returns Returns a const PointLight pointer that may be used to change
         *          lighting parameters.
         * @warning Do not add this type of light if Entity specified shaders do not support them.
         */
        static PointLight* create_point_light(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Creates a spot light that is positioned at (0, 0, 0) by default and adds the light
         * to the SceneGraph's vector of spot lights.
         * @param position The starting position of the light.
         * @returns Returns a const SpotLight pointer that may be used to change
         *          lighting parameters.
         * @warning Do not add this type of light if Entity specified shaders do not support them.
         */
        static SpotLight* create_spot_light(glm::vec3 position = glm::vec3(0.0f));
        /**
         * Creates a spot light that is positioned at (0, 0, 0) by default and adds the light
         * to the SceneGraph's vector of spot lights.
         * @param position The starting position of the light.
         * @returns Returns a const SpotLight pointer that may be used to change
         *          lighting parameters.
         * @warning Do not add this type of light if Entity specified shaders do not support them.
         */
        static SpotLight* create_spot_light(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Removes the specified light from the respective light's vector in the SceneGraph
         * @param A constant directional light pointer that will be used to remove the light from the vector.
         */
        static void remove_light(DirectionalLight* light);
        /**
         * Removes the specified light from the respective light's vector in the SceneGraph
         * @param A constant point light pointer that will be used to remove the light from the vector.
         */
        static void remove_light(PointLight* light);
        /**
         * Removes the specified light from the respective light's vector in the SceneGraph
         * @param A constant spot light pointer that will be used to remove the light from the vector.
         */
        static void remove_light(SpotLight* light);
    };
}
