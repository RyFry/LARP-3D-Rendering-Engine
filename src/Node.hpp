#pragma once

#include <memory>			    // shared_ptr
#include <unordered_map>	// unordered_map
#include <algorithm>      // find_if

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "LarpPrerequisites.hpp"
#include "Entity.hpp"

#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"

namespace Larp
{
    class Node
    {
    private:
        /**
         * The Entity object attached to this Node. Drawn during rendering.
         */
        UniqueEntity _entity;
        /**
         * This Node's parent Node.
         */
        Node* _parent;
        /**
         * All of this Node's child Node's. We use a map instead of a set
         * because std::unordered_set doesn't support non-const iterators
         */
        std::unordered_map<Node*, UniqueNode> _children;

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
        void draw(glm::mat4 model, glm::mat4& view, glm::mat4& projection, 
                  const glm::vec3& view_pos,
                  const std::vector<UniqueDirectional>& directional_lights,
                  const std::vector<UniquePoint>& point_lights,
                  const std::vector<UniqueSpot>& spot_lights);
        /**
         * Creates a new Node that is a child of this Node.
         * @return A pointer to the new Node
         */
        NodePtr create_child();
        /**
         * Removes a given pNode as a child of this Node object.
         * @return A pointer to the child was removed
         */
        NodePtr remove_child(NodePtr child);
        /**
         * Removes a given pNode as a child of this Node object.
         * @note After calling this function, child is still a valid pointer to a Node.
         * @note Use this function instead of delete_child if you wish to attach this
         *       child to another Node.
         */
        void delete_child(NodePtr child);
        /**
         * Attaches child to this Node, giving it ownership of the child.
         * @param child The Node to make a child of this node
         * @throws runtime_error if this child is attached to another Node.
         */
        void attach_child(NodePtr child);
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
         * Attaches an Entity to this object
         * @param entity The pointer to the Entity to attach to this object
         */
        void attach_entity(EntityPtr entity);
        /**
         * Deletes the Entity that this Node owns
         * @warning After this function is called, any pointers to this object's
         *          Entity are no longer valid.
         */
        void remove_entity();
        /**
         * Detaches the Entity that this Node owns
         * @warning This function should only be called if you are going to
         *          attach this Node's Entity to another Node.
         */
        EntityPtr detach_entity();
    };
}
