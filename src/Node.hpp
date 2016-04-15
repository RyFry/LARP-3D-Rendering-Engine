#pragma once

#include <memory>			// unique_ptr
#include <unordered_set>	// unordered_set

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Entity.hpp"

class Node;

typedef std::shared_ptr<Node> pNode;

class Node : public std::enable_shared_from_this<Node>
{
private:
    pEntity _entity;
    std::weak_ptr<Node> _parent;
    std::unordered_set<pNode> _children;

    glm::vec3 _position;
    glm::quat _rotation;
    glm::vec3 _scale;
public:
    Node();
    void draw(glm::mat4 model, glm::mat4& view, glm::mat4& projection);
    pNode create_child();
    pNode remove_child(pNode& child);
    void set_position(GLfloat x, GLfloat y, GLfloat z);
    void set_position(glm::vec3 position);
    void set_orientation(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void set_orientation(glm::quat rotation);
    void set_orientation(glm::vec3 axis, GLfloat w);
    void yaw(GLfloat yaw);
    void pitch(GLfloat pitch);
    void roll(GLfloat roll);
    void translate(GLfloat x, GLfloat y, GLfloat z);
    void translate(glm::vec3 vec);
    void set_scale(glm::vec3 scale);
    void set_scale(GLfloat x, GLfloat y, GLfloat z);
    void attach_entity(pEntity& entity);
    pEntity remove_entity();
};
