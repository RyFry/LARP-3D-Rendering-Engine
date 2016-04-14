#include "Node.hpp"

pNode Node::create_child()
{
	pNode tmp (new Node());
	tmp->_parent = shared_from_this();
	_children.insert(tmp);
	return tmp;
}

void Node::set_position(GLfloat z, GLfloat y, GLfloat z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

void Node::set_position(glm::vec3 position)
{
	_position = position;
}

void Node::set_orientation(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	_rotation.x = x;
	_rotation.y = y;
	_rotation.z = z;
	_rotation.w = w;
}

void Node::set_orientation(glm::quat rotation)
{
	_rotation = rotation;
}

void Node::set_orientation(glm::vec3 axis, GLfloat w)
{
	_rotation.x = axis.x;
	_rotation.y = axis.y;
	_rotation.z = axis.z;
	_rotation.w = w;
}