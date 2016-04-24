#pragma once

#include "PhysicsMeshCollider.hpp"

 class PhysicsMeshColliderBuilder
 {
 private:
 	btQuaternion _rotation;
 	btVector3 _position;
 	btScalar _mass;
 	btVector3 _local_inertia;
 	btScalar _restitution;
 public:
 	PhysicsMeshColliderBuilder();
 	void set_rotation(btQuaternion);
 	void set_position(btVector3);
 	void set_mass(btScalar);
 	void set_local_inertia(btVector3);
 	void set_restitution(btScalar);
 	PhysicsMeshColliderPtr build();
 };