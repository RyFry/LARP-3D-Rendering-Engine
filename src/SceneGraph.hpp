#pragma once

#include <memory>	// unique_ptr

#include "LarpPrerequisites.hpp"
#include "Node.hpp"

namespace Larp
{
    class SceneGraph
    {
    private:
        pNode _root;
        static pSceneGraph _singleton;
        SceneGraph();
    public:
        static pSceneGraph singleton();
        pNode create_child_node();
        void draw(glm::mat4& view, glm::mat4& projection);
        void set_ambient_light(glm::vec3 color);
    };
}
