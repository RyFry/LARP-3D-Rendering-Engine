#pragma once

#include "PhysicsObject.hpp"

template <typename BulletShape>
class PhysicsObjectBuilder
{
private:
    glm::quat _orientation;
    glm::vec3 _position;
    GLfloat _mass;
    glm::vec3 _local_inertia;
    GLfloat _restitution;
    Larp::Node* _user_pointer;

public:
    PhysicsObjectBuilder();
    /**
     * Set the orientation for the MeshCollider to be built by this object
     * @param orientation The orientation amount
     * @default (0, 0, 0, 1)
     */
    void set_orientation(glm::quat orientation);
    /**
     * Set the position for the MeshCollider to be built by this object
     * @param position The position amount
     * @default (0, 0, 0)
     */
    void set_position(glm::vec3 position);
    /**
     * Set the mass for the MeshCollider to be built by this object
     * A mass of 0.0 means that this object will not move or be affected
     * by gravity
     * @param mass The mass amount
     * @default 0.0
     */
    void set_mass(GLfloat mass);
    /**
     * Set the local inertia for the MeshCollider to be built by this object
     * @param local inertia The local inertia amount
     * @default (0, 0, 0)
     */
    void set_local_inertia(glm::vec3 local_inertia);
    /**
     * Set the restitution for the MeshCollider to be built by this object
     * @param restitution The restitution amount
     * @default 0.0
     */
    void set_restitution(GLfloat restitution);
    /**
     * Set the user pointer for the MeshCollider to be built by this object
     * @param user_pointer The user pointer amount
     * @default nullptr
     */
    void set_user_pointer(Larp::NodePtr user_pointer);
    PhysicsObject<BulletShape>* build();
};

