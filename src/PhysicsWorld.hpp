#pragma once

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "Error.hpp"

class PhysicsWorld
{
private:
  btDefaultCollisionConfiguration* _collision_configuration;
  btCollisionDispatcher* _dispatcher;
  btBroadphaseInterface* _overlapping_pair_cache;
  btSequentialImpulseConstraintSolver* _solver;
  btDiscreteDynamicsWorld* _dynamics_world;
  std::vector<btCollisionShape *> _collision_shape;
  std::map<std::string, btRigidBody *> _physics_accessors;
public:
  PhysicsWorld();
  ~PhysicsWorld();
  void init_objects();
  btDiscreteDynamicsWorld* get_dynamics_world();
  std::vector<btCollisionShape *>& get_collision_shapes();
  void track_rigid_body_with_name(btRigidBody* body, std::string& name);
  void track_rigid_body_with_name(btRigidBody* body, std::string&& name);
  size_t get_collision_object_count();
};

std::ostream& operator << (std::ostream& out, const btVector3& vec);
