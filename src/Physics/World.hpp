#pragma once

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "Larp/Error.hpp"

namespace Physics
{
    class World
    {
    private:
        btDefaultCollisionConfiguration* m_collision_configuration;
        btCollisionDispatcher* m_dispatcher;
        btBroadphaseInterface* m_overlapping_pair_cache;
        btSequentialImpulseConstraintSolver* m_solver;
        btDiscreteDynamicsWorld* m_dynamics_world;
        std::vector<btCollisionShape *> m_collision_shape;
        std::map<std::string, btRigidBody *> m_physics_accessors;
    public:
        World();
        ~World();
        void init_objects();
        btDiscreteDynamicsWorld* get_dynamics_world();
        std::vector<btCollisionShape *>& get_collision_shapes();
        void track_rigid_body_with_name(btRigidBody* body, std::string& name);
        void track_rigid_body_with_name(btRigidBody* body, std::string&& name);
        size_t get_collision_object_count();
    };
}

std::ostream& operator << (std::ostream& out, const btVector3& vec);
