#include "Node.hpp"

namespace Larp
{
    Node::Node()
        : m_scale(glm::vec3(1.0f, 1.0f, 1.0f))
    {}

    void Node::draw(glm::mat4 model, glm::mat4& view, glm::mat4& projection, const glm::vec3& view_pos)
    {
        glm::mat4 tmp_model = glm::translate(glm::mat4(), m_position);
        glm::mat4 rotation = glm::toMat4(m_rotation);
        tmp_model = tmp_model * rotation;
        tmp_model = glm::scale(tmp_model, m_scale);
        glm::mat4 my_model = model * tmp_model;

        if (m_entity != nullptr)
            m_entity->draw(my_model, view, projection, view_pos);
        for (auto& it : m_children)
            it.second->draw(my_model, view, projection, view_pos);
    }

    void Node::draw_shadows(const glm::mat4& model)
    {
        glm::mat4 tmp_model = glm::translate(glm::mat4(), m_position);
        glm::mat4 rotation = glm::toMat4(m_rotation);
        tmp_model = tmp_model * rotation;
        tmp_model = glm::scale(tmp_model, m_scale);
        glm::mat4 my_model = model * tmp_model;

        if (m_entity != nullptr)
            m_entity->draw_shadows(my_model);
        for (auto& it : m_children)
            it.second->draw_shadows(my_model);
    }

    Node* Node::create_child()
    {
        Node* tmp = new Node();
        tmp->m_parent = this;
        m_children[tmp] = UniqueNode(tmp);
        return tmp;
    }

    Node* Node::remove_child(Node* child)
    {
        Node* ret_val = child;
        auto it = m_children.find(ret_val);
        if (it == m_children.end())
        {
            PRINT_ERROR("Child is not a child of this Node. Removing nothing.");
            return child;
        }
        it->second.release();       // Make sure we don't delete the child we are removing
        ret_val->m_parent = nullptr; // Make the parent nullptr for testing when the user (possibly)
                                    // reatteches the Node somewhere else
        m_children.erase(it);
        return ret_val;
    }

    void Node::delete_child(Node* child)
    {
        auto it = m_children.find(const_cast<Node*>(child));
        if (it == m_children.end())
        {
            PRINT_ERROR("Child is not a child of this Node. Removing nothing.");
        }
        m_children.erase(it);
    }

    void Node::attach_child(Node* child)
    {
        if (child->m_parent != nullptr)
        {
            THROW_RUNTIME_ERROR("This child is already attached to another Node");
        }

        Node* tmp = child;
        m_children[tmp] = UniqueNode(tmp);
        tmp->m_parent = this;
    }

    void Node::detach_this_from_parent()
    {
        if (m_parent == nullptr)
        {
            PRINT_ERROR("This child is not attached to a Node. Ignoring.");
            return;
        }

        m_parent->remove_child(this);
    }

    void Node::delete_this_from_scene()
    {
        if (m_parent == nullptr)
        {
            PRINT_ERROR("This child is not attached to a Node. Ignoring.");
            return;
        }

        m_parent->delete_child(this);
    }

    void Node::set_position(GLfloat x, GLfloat y, GLfloat z)
    {
        m_position.x = x;
        m_position.y = y;
        m_position.z = z;
    }

    void Node::set_position(glm::vec3 position)
    {
        m_position = position;
    }

    glm::vec3 Node::get_position()
    {
        return m_position;
    }

    void Node::set_orientation(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
        m_rotation = glm::angleAxis(w, glm::vec3(x, y, z));
    }

    void Node::set_orientation(glm::quat rotation)
    {
        m_rotation = rotation;
    }

    void Node::set_orientation(glm::vec3 axis, GLfloat w)
    {
        m_rotation = glm::angleAxis(w, axis);
    }

    void Node::yaw(GLfloat yaw)
    {
        m_rotation = glm::rotate(m_rotation,
                                      yaw,
                                      glm::vec3(0, 1, 0));
    }

    void Node::pitch(GLfloat pitch)
    {
        m_rotation = glm::rotate(m_rotation,
                                      pitch,
                                      glm::vec3(1, 0, 0));
    }

    void Node::roll(GLfloat roll)
    {
        m_rotation = glm::rotate(m_rotation,
                                      roll,
                                      glm::vec3(0, 0, 1));
    }

    void Node::translate(GLfloat x, GLfloat y, GLfloat z)
    {
        m_position += glm::vec3(x, y, z);
    }

    void Node::translate(glm::vec3 vec)
    {
        m_position += vec;
    }

    void Node::set_scale(glm::vec3 scale)
    {
        m_scale = scale;
    }

    void Node::set_scale(GLfloat x, GLfloat y, GLfloat z)
    {
        m_scale.x = x;
        m_scale.y = y;
        m_scale.z = z;
    }

    glm::vec3 Node::get_scale() const
    {
        return m_scale;
    }

    void Node::attach_entity(Entity* entity)
    {
        m_entity.reset(entity);
    }

    void Node::remove_entity()
    {
        m_entity.reset(nullptr);
    }

    Entity* Node::detach_entity()
    {
        return m_entity.release();
    }

    GLfloat Node::get_scaled_width() const
    {
        return m_entity->get_width() * m_scale.x;
    }

    GLfloat Node::get_scaled_height() const
    {
        return m_entity->get_height() * m_scale.y;
    }

    GLfloat Node::get_scaled_depth() const
    {
        return m_entity->get_depth() * m_scale.z;
    }

    glm::vec3 Node::get_scaled_bounding_box() const
    {
        return glm::vec3(m_entity->get_width() * m_scale.x,
                         m_entity->get_height() * m_scale.y,
                         m_entity->get_depth() * m_scale.z);
    }
}
