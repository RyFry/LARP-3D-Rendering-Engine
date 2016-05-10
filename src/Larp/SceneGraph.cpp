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

        std::vector<UniqueDirectional>& dir_lights = LightFactory::_directional_lights;
        if (Shader::_shadow_shader && !dir_lights.empty())
        {
            GLfloat near_plane = 0.1f; 
            GLfloat far_plane_change = 100.0f / NUM_SHADOW_MAPS;
            GLfloat cur_far_plane = 0.0f;

            // The closest shadow map must have the highest resolution which is determined by the index to the power of 2
            for (GLint i = NUM_SHADOW_MAPS - 1; i >= 0; --i)
            {
                cur_far_plane += far_plane_change;
                Shader::_light_space_matrix.at(i) = Shader::calculate_light_space_matrix(dir_lights[0]->_direction, near_plane, cur_far_plane);
                Shader::_shadow_shader->use();
                Shader::_shadow_shader->set_light_space_matrix(Shader::_light_space_matrix.at(i));

                Shader::prepare_depth_map(i);
                this->_root->draw_shadows(identity);
                Shader::unbind_depth_map();

                identity = glm::mat4();
            }
        }
        // ... draw the actual scene...
        this->_root->draw(identity, view, projection, view_pos);

        if (this->_skybox != nullptr)
            this->_skybox->draw(view, projection);
    }

    void SceneGraph::set_skybox(SkyBox* skybox)
    {
        this->_skybox = skybox;
    }
}
