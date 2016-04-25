#pragma once

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

#include "Model.hpp"

typedef PhysicsMeshCollider* const PhysicsMeshColliderPtr;

class PhysicsMeshCollider
{
    btRigidBody* _rigid_body;
	PhysicsMeshCollider(ModelPtr model, btQuaternion rotation, btPosition position,
                        btScalar mass, btVector3 local_inertia, btScalar restitution);
};
