#include "SceneGraph.hpp"
namespace Larp
{
    const size_t SceneGraph::_max_directional_lights = 1;
    const size_t SceneGraph::_max_point_lights = 9;
    const size_t SceneGraph::_max_spot_lights = 0;

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

    void SceneGraph::draw(glm::mat4& view, glm::mat4& projection, const glm::vec3& view_pos)
    {
        glm::mat4 identity;
        this->_root->draw(identity, view, projection, view_pos, this->_directional_lights,
                          this->_point_lights, this->_spot_lights);
        this->_skybox->draw(view, projection);
    }

    DirectionalLightPtr SceneGraph::create_directional_light(glm::vec3 direction)
    {
        if (this->_directional_lights.size() >= this->_max_directional_lights + 1)
        {
            THROW_RUNTIME_ERROR("Only " << this->_max_directional_lights << " directional light(s) allowed");
        }

        this->_directional_lights.push_back(UniqueDirectional(new DirectionalLight(direction.x, direction.y, direction.z)));
        return this->_directional_lights.back().get();
    }

    DirectionalLightPtr SceneGraph::create_directional_light(GLfloat x, GLfloat y, GLfloat z)
    {
        if (this->_directional_lights.size() >= this->_max_directional_lights + 1)
        {
            THROW_RUNTIME_ERROR("Only " << this->_max_directional_lights << " directional light(s) allowed");
        }

        this->_directional_lights.push_back(UniqueDirectional(new DirectionalLight(x, y, z)));
        return this->_directional_lights.back().get();
    }

    PointLightPtr SceneGraph::create_point_light(glm::vec3 position)
    {
        if (this->_point_lights.size() >= this->_max_point_lights + 1)
        {
            THROW_RUNTIME_ERROR("Only " << this->_max_point_lights << " point light(s) allowed");
        }

        this->_point_lights.push_back(UniquePoint(new PointLight(position.x, position.y, position.z)));
        return this->_point_lights.back().get();
    }

    PointLightPtr SceneGraph::create_point_light(GLfloat x, GLfloat y, GLfloat z)
    {
        if (this->_point_lights.size() >= this->_max_point_lights + 1)
        {
            THROW_RUNTIME_ERROR("Only " << this->_max_point_lights << " point light(s) allowed");
        }

        this->_point_lights.push_back(UniquePoint(new PointLight(x, y, z)));
        return this->_point_lights.back().get();
    }

    SpotLightPtr SceneGraph::create_spot_light(glm::vec3 position)
    {
        if (this->_spot_lights.size() >= this->_max_spot_lights + 1)
        {
            THROW_RUNTIME_ERROR("Only " << this->_max_spot_lights << " spot light(s) allowed");
        }

        this->_spot_lights.push_back(UniqueSpot(new SpotLight(position.x, position.y, position.z)));
        return this->_spot_lights.back().get();
    }

    SpotLightPtr SceneGraph::create_spot_light(GLfloat x, GLfloat y, GLfloat z)
    {
        if (this->_spot_lights.size() >= this->_max_spot_lights + 1)
        {
            THROW_RUNTIME_ERROR("Only " << this->_max_spot_lights << " spot light(s) allowed");
        }

        this->_spot_lights.push_back(UniqueSpot(new SpotLight(x, y, z)));
        return this->_spot_lights.back().get();
    }

    void SceneGraph::remove_light(DirectionalLightPtr light)
    {
        auto func = [light] (UniqueDirectional& l) -> bool
        {
            return light == l.get();
        };

        auto it = std::find_if(this->_directional_lights.begin(), this->_directional_lights.end(), func);
        if (it == this->_directional_lights.end())
        {
            PRINT_ERROR("Directional light not found");
        }
        else
        {
            it->reset(nullptr);
            this->_directional_lights.erase(it);
        }
    }

    void SceneGraph::remove_light(PointLightPtr light)
    {
        auto func = [light] (UniquePoint& l) -> bool
        {
            return light == l.get();
        };

        auto it = std::find_if(this->_point_lights.begin(), this->_point_lights.end(), func);
        if (it == this->_point_lights.end())
        {
            PRINT_ERROR("Point light not found");
        }
        else
        {
            it->reset(nullptr);
            this->_point_lights.erase(it);
        }
    }

    void SceneGraph::remove_light(SpotLightPtr light)
    {
        auto func = [light] (UniqueSpot& l) -> bool
        {
            return light == l.get();
        };

        auto it = std::find_if(this->_spot_lights.begin(), this->_spot_lights.end(), func);
        if (it == this->_spot_lights.end())
        {
            PRINT_ERROR("Spot light not found");
        }
        else
        {
            it->reset(nullptr);
            this->_spot_lights.erase(it);
        }
    }

    void SceneGraph::set_skybox(SkyBox* skybox)
    {
        this->_skybox = skybox;
    }
}
