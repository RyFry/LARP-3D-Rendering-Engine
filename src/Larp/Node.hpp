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
        UniqueEntity m_entity;
        /**
         * This Node's parent Node.
         */
        Node* m_parent;
        /**
         * All of this Node's child Node's. We use a map instead of a set
         * because std::unordered_set doesn't support non-const iterators
         */
        std::unordered_map<Node*, UniqueNode> m_children;
        /**
         * This Node's position
         */
        glm::vec3 m_position;
        /**
         * This Node's rotation
         */
        glm::quat m_rotation;
        /**
         * This Node's scale
         */
        glm::vec3 m_scale;
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
         * @param view_pos The camera view position to apply during rendering.
         *                 This should be obtained from a Camera object and passed in
         *                 via the SceneGraph.
         * @param directional_lights The vector of directional lights currently held
         *                           by the SceneGraph.
         * @param point_lights The vector of point lights currently held
         *                      by the SceneGraph.
         * @param spot_lights The vector of spot lights currently held
         *                    by the SceneGraph.
         * @note the order in which the draw method is called on the Node's children is
         *       not necessarily the order in which they were created.
         */
        void draw(glm::mat4 model, glm::mat4& view, glm::mat4& projection, const glm::vec3& view_pos);
        void draw_shadows(const glm::mat4& model);
        /**
         * Creates a new Node that is a child of this Node.
         * @return A pointer to the new Node
         */
        Node* create_child();
        /**
         * Removes a given Node as a child of this Node object.
         * @note After calling this function, child is still a valid pointer to a Node.
         * @note Use this function instead of delete_child if you wish to attach this
         *       child to another Node.
         */
        Node* remove_child(Node* child);
        /**
         * Removes and deletes a given Node that is a child of this Node object.
         */
        void delete_child(Node* child);
        /**
         * Attaches child to this Node, giving it ownership of the child.
         * @param child The Node to make a child of this node
         * @throws runtime_error if this child is attached to another Node.
         */
        void attach_child(Node* child);
        /**
         * Detaches this Node from its parent, but does not delete it, so that
         * it may be reattached elsewhere.
         * @warning If this node is not needed elsewhere, please use Node::delete_this_from_scene
         */
        void detach_this_from_parent();
        /**
         * Detaches this Node from its parent, deleting it in the process
         * @warning Any pointer to this Node after this is called is no longer valid
         * @warning If you intend to reattech this Node somewhere else in the SceneGraph,
         *          please use Node::detach_this_from_parent
         */
        void delete_this_from_scene();
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
         * @return This Node's position relative to its parent
         */
        glm::vec3 get_position();
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
         * @return the scale of this Node
         */
        glm::vec3 get_scale() const;
        /**
         * Attaches an Entity to this object
         * @param entity The pointer to the Entity to attach to this object
         */
        void attach_entity(Entity* entity);
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
        Entity* detach_entity();

        GLfloat get_scaled_width() const;
        GLfloat get_scaled_height() const;
        GLfloat get_scaled_depth() const;
        glm::vec3 get_scaled_bounding_box() const;
    };
}
