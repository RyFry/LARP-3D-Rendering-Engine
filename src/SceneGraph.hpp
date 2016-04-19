#pragma once

#include <memory>	// unique_ptr

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
        pNode _root;
        /**
         * A Singleton instance of the SceneGraph class that prevents
         * users from making more than one SceneGraph.
         */
        static pSceneGraph _singleton;
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
        static pSceneGraph singleton();
        /**
         * Creates a new child on the root Node of the SceneGraph
         * @return The new child node attached to the root
         * @note The new child may not come before the other children
         *       during rendering
         */
        pNode create_child_node();
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
        void draw(glm::mat4& view, glm::mat4& projection);
        /**
         * Sets ambient lighting
         * @param color The color to set the ambient lighting to.
         * @warning This function is currently unimplemented and does nothing. <b>Do not call this function!</b>
         */
        void set_ambient_light(glm::vec3 color);
    };
}
