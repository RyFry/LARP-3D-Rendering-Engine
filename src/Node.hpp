#pragma once

#include <memory>			// shared_ptr
#include <unordered_set>	// unordered_set

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

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
         * This Node's position
         */
        glm::vec3 _position;
        /**
         * This Node's rotation
         */
        glm::quat _rotation;
        /**
         * This Node's scale
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
         * @note the order in which the draw method is called on the Node's children is
         *       not necessarily the order in which they were created.
         */
        void draw(glm::mat4 model, glm::mat4& view, glm::mat4& projection);
        /**
         * Creates a new Node that is a child of this Node.
         * @return A pointer to the new Node
         */
        pNode create_child();
        /**
         * Removes a given pNode as a child of this Node object.
         * @return the pNode that was removed
         */
        pNode remove_child(pNode& child);
        /**
         * Sets the position of this Node
         * @param x The new x position.
         * @param y The new y position.
         * @param z The new z position.
         */
        void set_position(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Sets the position of this Node
         * @param position The new position of this Node
         */
        void set_position(glm::vec3 position);
        /**
         * Sets the orientation of this Node
         * @param x The x-direction of the axis of rotation
         * @param y The y-direction of the axis of rotation
         * @param z The z-direction of the axis of rotation
         * @param w The angular component of the rotation, in degrees
         * @note This function expects w in degrees
         * @warning This function expects an expanded version of the (axis, angle)
         *          quaternion representation, @b not the same 4-components
         *          that glm::quat(w, x, y, z) expect.
         */
        void set_orientation(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
        /**
         * Sets the orientation of this Node
         * @param rotation The amount to rotate this Node
         * @warning This function expects a properly computed glm::quat,
         *          such as one obtained by calling glm::angleAxis().
         */
        void set_orientation(glm::quat rotation);
        /**
         * Sets the orientation of this Node
         * @param axis The axis of rotation
         * @param w The angle of rotation, in degrees
         * @note This function expects w in degrees
         */
        void set_orientation(glm::vec3 axis, GLfloat w);
        /**
         * Yaws the Node
         * @param yaw The degrees to yaw this Node
         * @note This function expects yaw in degrees
         * @note This function adds to any yaw amount already applied to the Node
         */
        void yaw(GLfloat yaw);
        /**
         * Pitchs the Node
         * @param pitch The degrees to pitch this Node
         * @note This function expects pitch in degrees
         * @note This function adds to any pitch amount already applied to the Node
         */
        void pitch(GLfloat pitch);
        /**
         * Rolls the Node
         * @param roll The degrees to roll this Node
         * @note This function expects roll in degrees
         * @note This function adds to any roll amount already applied to the Node
         */
        void roll(GLfloat roll);
        /**
         * Translates the Node
         * @param x The number of units in the x-direction to translate this Node
         * @param y The number of units in the y-direction to translate this Node
         * @param z The number of units in the z-direction to translate this Node
         * @note This function adds to any translation amount already applied to the Node
         */
        void translate(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Translates the Node
         * @param vec The number of units to translate this Node in the x-, y-, and z-directions
         * @note This function adds to any translation amount already applied to the Node
         */
        void translate(glm::vec3 vec);
        /**
         * Scales the Node
         * @param scale The number of units to scale this Node in the x-, y-, and z-directions
         */
        void set_scale(glm::vec3 scale);
        /**
         * Scales the Node
         * @param x The number of units to scale this Node in the x-direction
         * @param y The number of units to scale this Node in the y-direction
         * @param z The number of units to scale this Node in the z-direction
         */
        void set_scale(GLfloat x, GLfloat y, GLfloat z);
        /**
         * Attaches a pEntity to this object
         * @param entity The pEntity to attach to this object
         */
        void attach_entity(pEntity& entity);
        /**
         * Detaches the pEntity from this Node
         * @return the pEntity that was removed from this Node
         */
        pEntity remove_entity();
    };
}
