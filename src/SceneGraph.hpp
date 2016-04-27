#pragma once

#include <algorithm>
#include <vector>

#include "LarpPrerequisites.hpp"
#include "Node.hpp"

namespace Larp
{
    class SceneGraph
    {
    private:
        /**
         * The root pNode of this SceneGraph
         */
        UniqueNode _root;
        /**
         * A Singleton instance of the SceneGraph class that prevents
         * users from making more than one SceneGraph.
         */
        static UniqueSceneGraph _singleton;
        /**
         * The vector of directional lights currently held by the SceneGraph.
         * If the vector is not empty, these will eventually be incorporated 
         * in the lighting calculations after they are passed from the SceneGraph
         * to the Node(s) and eventually and Entity.
         */
        std::vector<UniqueDirectional> _directional_lights;
        /**
         * The vector of point lights currently held by the SceneGraph.
         * If the vector is not empty, these will eventually be incorporated 
         * in the lighting calculations after they are passed from the SceneGraph
         * to the Node(s) and eventually and Entity.
         */
        std::vector<UniquePoint> _point_lights;
        /**
         * The vector of spot lights currently held by the SceneGraph.
         * If the vector is not empty, these will eventually be incorporated 
         * in the lighting calculations after they are passed from the SceneGraph
         * to the Node(s) and eventually and Entity.
         */
        std::vector<UniqueSpot> _spot_lights;
        /**
         * This is the maximum number of directional lights that may be added to the SceneGraph
         */
        static const size_t _max_directional_lights;
        /**
         * This is the maximum number of point lights that may be added to the SceneGraph
         */
        static const size_t _max_point_lights;
        /**
         * This is the maximum number of spot lights that may be added to the SceneGraph
         * @warning SpotLights are not currently supported.
         */
        static const size_t _max_spot_lights;
        /**
         * Default constructor. Made private to avoid having multiple
         * SceneGraph's per program.
         */
        SceneGraph();
    public:
        /**
         * Returns the single instance of SceneGraph
         * @return The singleton instance of SceneGraph
         */
        static SceneGraphPtr singleton();
        /**
         * Creates a new child on the root Node of the SceneGraph
         * @return The new child node attached to the root
         * @note The new child may not come before the other children
         *       during rendering
         */
        NodePtr create_child_node();
        /**
         * Clears all Nodes from the SceneGraph
         */
        void clear();
        /**
         * Draws out every node in the SceneGraph by performing a
         * depth-first traversal on each Node.
         * @param view The view matrix provided by the camera to be passed to each Node's
         *             shader program.
         * @param projection The project matrix determined by the field of view to be
         *                   passed to each Node's shader program.
         * @param view_pos The camera view position to apply during rendering.
         *                 This should be obtained from a Camera object.
         */
        void draw(glm::mat4& view, glm::mat4& projection, const glm::vec3& view_pos);
        /**
         * Creates a directional light that faces downwards by default and adds the light
         * to the SceneGraph's vector of directional lights.
         * @param direction The direction the light should be facing.
         * @returns Returns a const DirectionalLight pointer that may be used to change
         *          lighting parameters.
         * @warning Do not add this type of light if Entity specified shaders do not support them.
         */
        DirectionalLightPtr create_directional_light(glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f));
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
        DirectionalLightPtr create_directional_light(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Creates a point light that is positioned at (0, 0, 0) by default and adds the light
         * to the SceneGraph's vector of point lights.
         * @param position The starting position of the light.
         * @returns Returns a const PointLight pointer that may be used to change
         *          lighting parameters.
         * @warning Do not add this type of light if Entity specified shaders do not support them.
         */
        PointLightPtr create_point_light(glm::vec3 position = glm::vec3(0.0f));
        /**
         * Creates a point light that is positioned at (0, 0, 0) by default and adds the light
         * to the SceneGraph's vector of point lights.
         * @param position The starting position of the light.
         * @returns Returns a const PointLight pointer that may be used to change
         *          lighting parameters.
         * @warning Do not add this type of light if Entity specified shaders do not support them.
         */
        PointLightPtr create_point_light(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Creates a spot light that is positioned at (0, 0, 0) by default and adds the light
         * to the SceneGraph's vector of spot lights.
         * @param position The starting position of the light.
         * @returns Returns a const SpotLight pointer that may be used to change
         *          lighting parameters.
         * @warning Do not add this type of light if Entity specified shaders do not support them.
         */
        SpotLightPtr create_spot_light(glm::vec3 position = glm::vec3(0.0f));
        /**
         * Creates a spot light that is positioned at (0, 0, 0) by default and adds the light
         * to the SceneGraph's vector of spot lights.
         * @param position The starting position of the light.
         * @returns Returns a const SpotLight pointer that may be used to change
         *          lighting parameters.
         * @warning Do not add this type of light if Entity specified shaders do not support them.
         */
        SpotLightPtr create_spot_light(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Removes the specified light from the respective light's vector in the SceneGraph
         * @param A constant directional light pointer that will be used to remove the light from the vector.
         */
        void remove_light(DirectionalLightPtr light);
        /**
         * Removes the specified light from the respective light's vector in the SceneGraph
         * @param A constant point light pointer that will be used to remove the light from the vector.
         */
        void remove_light(PointLightPtr light);
        /**
         * Removes the specified light from the respective light's vector in the SceneGraph
         * @param A constant spot light pointer that will be used to remove the light from the vector.
         */
        void remove_light(SpotLightPtr light);
    };
}
