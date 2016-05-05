#pragma once

#include "PhysicsWorld.hpp"

class PhysicsObject
{
private:
    btRigidBody* _rigid_body;
public:
    PhysicsObject();
    btRigidBody* get_rigid_body() const;
};

typedef PhysicsObject* PhysicsObjectPtr;
