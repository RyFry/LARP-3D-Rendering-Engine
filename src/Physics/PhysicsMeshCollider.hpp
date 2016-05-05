#pragma once

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

#include "Larp/Model.hpp"
#include "Larp/Node.hpp"

class PhysicsMeshCollider
{
private:
    btRigidBody* _rigid_body;

public:
    PhysicsMeshCollider(Larp::ModelPtr model, glm::quat rotation, glm::vec3 position,
                        GLfloat mass, glm::vec3 local_inertia, GLfloat restitution,
                        Larp::NodePtr user_pointer);
    btRigidBody* get_rigid_body() const;
};

typedef PhysicsMeshCollider* PhysicsMeshColliderPtr;
