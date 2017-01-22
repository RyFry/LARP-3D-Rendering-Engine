#include "SceneGraph.hpp"

namespace Larp
{
    const size_t SceneGraph::sc_max_directional_lights = 1;
    const size_t SceneGraph::sc_max_point_lights = 9;
    const size_t SceneGraph::sc_max_spot_lights = 0;

    UniqueSceneGraph SceneGraph::s_singleton(nullptr);

    SceneGraph::SceneGraph()
        : m_root(new Node())
    {
    }

    SceneGraph* SceneGraph::singleton()
    {
        if (!s_singleton)
        {
            s_singleton.reset(new SceneGraph());
        }
        return s_singleton.get();
    }

    Node* SceneGraph::create_child_node()
    {
        return m_root->create_child();
    }

    Node* SceneGraph::get_root_node()
    {
        return m_root.get();
    }

    void SceneGraph::clear()
    {
        /*
         * Since we're using unique_ptr's, resetting _root by making it
         * point to new Node object will delete the current root, which
         * will cascade and subsequently delete all of its children
         */
        m_root.reset(new Node());
    }

    void SceneGraph::draw(glm::mat4& view, glm::mat4& projection, const glm::vec3& view_pos)
    {
        glm::mat4 identity;
        std::vector<UniqueDirectional>& dir_lights = LightFactory::s_directional_lights;
        if (Shader::s_shadow_shader && !dir_lights.empty())
        {
            Shader::s_light_space_matrix = Shader::calculate_light_space_matrix(dir_lights[0]->m_direction);
            Shader::s_shadow_shader->use();
            Shader::s_shadow_shader->set_light_space_matrix(Shader::s_light_space_matrix);

            Shader::prepare_depth_map();
            m_root->draw_shadows(identity);
            Shader::unbind_depth_map();
        }
        // ... draw the actual scene...

        identity = glm::mat4();
        m_root->draw(identity, view, projection, view_pos);

        if (m_skybox != nullptr)
            m_skybox->draw(view, projection);
    }

    void SceneGraph::set_skybox(SkyBox* skybox)
    {
        m_skybox = skybox;
    }
}
