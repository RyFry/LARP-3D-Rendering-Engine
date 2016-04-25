#pragma once

#include <string>

#include "PhysicsMeshCollider.hpp"
#include "Model.hpp"

class PhysicsMeshColliderBuilder
{
private:
    Larp::ModelPtr _model;
 	btQuaternion _rotation;
 	btVector3 _position;
 	btScalar _mass;
 	btVector3 _local_inertia;
 	btScalar _restitution;
public:
 	PhysicsMeshColliderBuilder(std::string path);
 	void set_rotation(btQuaternion rotation);
 	void set_position(btVector3 position);
 	void set_mass(btScalar mass);
 	void set_local_inertia(btVector3 local_inertia);
 	void set_restitution(btScalar restitution);
 	PhysicsMeshColliderPtr build();
};
