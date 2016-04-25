#pragma once

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

#include "Model.hpp"

class PhysicsMeshCollider
{
private:
    btRigidBody* _rigid_body;

public:
    PhysicsMeshCollider(Larp::ModelPtr model, btQuaternion rotation, btVector3 position,
                        btScalar mass, btVector3 local_inertia, btScalar restitution,
                        void * user_pointer);
    btRigidBody* get_rigid_body() const;
};

typedef PhysicsMeshCollider* const PhysicsMeshColliderPtr;
