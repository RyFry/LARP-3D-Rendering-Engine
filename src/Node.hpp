#pragma once

#include <memory>			// unique_ptr
#include <unordered_set>	// unordered_set

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Entity.hpp"

class Node;

typedef std::shared_ptr<Node> pNode;
typedef std::shared_ptr<Entity> pEntity;

class Node : std::enable_shared_from_this<Node>
{
private:
	pEntity _entity;
	std::weak_ptr<Node> _parent;
	std::unordered_set<Node> _children;

	glm::vec3 _position;
	glm::quat _rotation;
	glm::vec3 _scale;
public:
	pNode create_child();
};
