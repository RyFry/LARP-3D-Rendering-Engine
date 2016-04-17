#pragma once

#include <memory>			// shared_ptr
#include <unordered_set>	// unordered_set

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "LarpPrerequisites.hpp"
#include "Entity.hpp"

namespace Larp
{
    class Node : public std::enable_shared_from_this<Node>
    {
    private:
        /**
         * The Entity object attached to this Node. Drawn during rendering.
         */
        pEntity _entity;
        /**
         * This Node's parent Node. 
         */
        std::weak_ptr<Node> _parent;
        /**
         * All of this Node's child Node's
         */
        std::unordered_set<pNode> _children;

        /**
         * This Node's position relative to its parent
         */
        glm::vec3 _position;
        /**
         * This Node's rotation relative to its parent
         */
        glm::quat _rotation;
        /**
         * This Node's scale relative to its parent
         */
        glm::vec3 _scale;
    public:
        /**
         * Default Constructor
         * Initializes the Node to be at the parent's origin, unrotated relative to
         * the parent, and to have the same scale as the parent
         */
        Node();
        /**
         * Draws the Entity attached to this node using this Node's derived model matrix,
         * then recursively calls the draw method on each of this Node's children.
         * @note the order in which the draw method is called on children is not necessarily
         *       the order in which they were created.
         */
        void draw(glm::mat4 model, glm::mat4& view, glm::mat4& projection);
        /**
         * Creates a child node
         */
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
}
