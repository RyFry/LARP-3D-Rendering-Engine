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

        std::vector<UniqueDirectional> _directional_lights;

        std::vector<UniquePoint> _point_lights;

        std::vector<UniqueSpot> _spot_lights;

        static const size_t _max_directional_lights;

        static const size_t _max_point_lights;

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
         */
        void draw(glm::mat4& view, glm::mat4& projection, const glm::vec3& view_pos);

        DirectionalLightPtr create_directional_light(glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f));

        DirectionalLightPtr create_directional_light(GLfloat x, GLfloat y, GLfloat z);

        PointLightPtr create_point_light(glm::vec3 position = glm::vec3(0.0f));

        PointLightPtr create_point_light(GLfloat x, GLfloat y, GLfloat z);

        SpotLightPtr create_spot_light(glm::vec3 position = glm::vec3(0.0f));

        SpotLightPtr create_spot_light(GLfloat x, GLfloat y, GLfloat z);

        void remove_light(DirectionalLightPtr light);

        void remove_light(PointLightPtr light);

        void remove_light(SpotLightPtr light);
    };
}
