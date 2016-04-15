#include "Node.hpp"

Node::Node()
{
    this->_scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Node::draw(glm::mat4 model, glm::mat4& view, glm::mat4& projection)
{
    glm::mat4 tmp_model = glm::translate(glm::mat4(), this->_position);
    glm::mat4 rotation = glm::mat4_cast(this->_rotation);
    tmp_model = tmp_model * rotation;
    tmp_model = glm::scale(tmp_model, this->_scale);
    glm::mat4 my_model = model * tmp_model;
    if (this->_entity != nullptr)
        this->_entity->draw(my_model, view, projection);
    for (auto& it : this->_children)
        it->draw(my_model, view, projection);
}

pNode Node::create_child()
{
    pNode tmp(new Node());
    tmp->_parent = shared_from_this();
    this->_children.insert(tmp);
    return tmp;
}

pNode Node::remove_child(pNode& child)
{
    this->_children.erase(child);
    return child;
}

void Node::set_position(GLfloat x, GLfloat y, GLfloat z)
{
    this->_position.x = x;
    this->_position.y = y;
    this->_position.z = z;
}

void Node::set_position(glm::vec3 position)
{
    this->_position = position;
}

void Node::set_orientation(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    this->_rotation.x = x;
    this->_rotation.y = y;
    this->_rotation.z = z;
    this->_rotation.w = w;
}

void Node::set_orientation(glm::quat rotation)
{
    this->_rotation = rotation;
}

void Node::set_orientation(glm::vec3 axis, GLfloat w)
{
    this->_rotation.x = axis.x;
    this->_rotation.y = axis.y;
    this->_rotation.z = axis.z;
    this->_rotation.w = w;
}

void Node::yaw(GLfloat yaw)
{
    this->_rotation = glm::rotate(this->_rotation,
                                  glm::radians(yaw),
                                  glm::vec3(0, 1, 0));
}

void Node::pitch(GLfloat pitch)
{
    this->_rotation = glm::rotate(this->_rotation,
                                  glm::radians(pitch),
                                  glm::vec3(1, 0, 0));
}

void Node::roll(GLfloat roll)
{
    this->_rotation = glm::rotate(this->_rotation,
                                  glm::radians(roll),
                                  glm::vec3(0, 0, 1));
}

void Node::translate(GLfloat x, GLfloat y, GLfloat z)
{
    this->_position += glm::vec3(x, y, z);
}

void Node::translate(glm::vec3 vec)
{
    this->_position += vec;
}

void Node::set_scale(glm::vec3 scale)
{
    this->_scale = scale;
}

void Node::set_scale(GLfloat x, GLfloat y, GLfloat z)
{
    this->_scale.x = x;
    this->_scale.y = y;
    this->_scale.z = z;
}

void Node::attach_entity(pEntity& entity)
{
    this->_entity = entity;
}

pEntity Node::remove_entity()
{
    pEntity tmp = this->_entity;
    this->_entity = pEntity(nullptr);
    return tmp;
}
