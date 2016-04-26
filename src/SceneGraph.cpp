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

    DirectionalLightPtr SceneGraph::create_directional_light()
    {
        this->_directional_lights.push_back(UniqueDirectional(new DirectionalLight()));
        return this->_directional_lights.back().get();
    }

    PointLightPtr SceneGraph::create_point_light()
    {
        this->_point_lights.push_back(UniquePoint(new PointLight()));
        return this->_point_lights.back().get();
    }

    SpotLightPtr SceneGraph::create_spot_light()
    {
        this->_spot_lights.push_back(UniqueSpot(new SpotLight()));
        return this->_spot_lights.back().get();
    }
}
