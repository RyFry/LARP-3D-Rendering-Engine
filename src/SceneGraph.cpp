#include "SceneGraph.hpp"
namespace Larp
{
    UniqueSceneGraph SceneGraph::_singleton(nullptr);

    SceneGraph::SceneGraph()
        : _root(new Node())
    {
    }

    SceneGraphPtr SceneGraph::singleton()
    {
        if (!_singleton)
        {
            _singleton.reset(new SceneGraph());
        }
        return _singleton.get();
    }

    NodePtr SceneGraph::create_child_node()
    {
        return _root->create_child();
    }

    void SceneGraph::clear()
    {
        /*
         * Since we're using shared_ptr's, resetting _root by making it
         * point to new Node object will delete the current root, which
         * will cascade and subsequently delete all of its children
         * (Assuming the user doesn't have any saved copies of the Node's
         * already in the SceneGraph)
         */
        this->_root.reset(new Node());
    }

    void SceneGraph::draw(glm::mat4& view, glm::mat4& projection)
    {
        glm::mat4 identity;
        this->_root->draw(identity, view, projection);
    }

    void SceneGraph::set_ambient_light(glm::vec3 color)
    {
    }
}
