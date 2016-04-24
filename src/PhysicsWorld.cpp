#include "PhysicsWorld.hpp"

// std::ostream& operator << (std::ostream& out, const btVector3& vec)
// {
//   out << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")";
// }

PhysicsWorld::PhysicsWorld()
    : _collision_configuration(0),
      _dispatcher(0),
      _overlapping_pair_cache(0),
      _solver(0),
      _dynamics_world(0)
{
}

PhysicsWorld::~PhysicsWorld() 
{
    if (_collision_configuration) delete _collision_configuration;
    if (_dispatcher) delete _dispatcher;
    if (_overlapping_pair_cache) delete _overlapping_pair_cache;
    if (_solver) delete _solver;
    if (_dynamics_world) delete _dynamics_world;
}

void PhysicsWorld::init_objects()
{
    _collision_configuration = new btDefaultCollisionConfiguration();
    _dispatcher = new btCollisionDispatcher(_collision_configuration);
    _overlapping_pair_cache = new btDbvtBroadphase();
    _overlapping_pair_cache->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
    _solver = new btSequentialImpulseConstraintSolver();
    _dynamics_world = new btDiscreteDynamicsWorld(_dispatcher,
                                                 _overlapping_pair_cache,
                                                 _solver,
                                                 _collision_configuration);
}

btDiscreteDynamicsWorld* PhysicsWorld::get_dynamics_world()
{
    return this->_dynamics_world;
}

std::vector<btCollisionShape *>& PhysicsWorld::get_collision_shapes()
{
    return this->_collision_shape;
}

void PhysicsWorld::track_rigid_body_with_name(btRigidBody* body, std::string& name)
{
    if (this->_physics_accessors.find(name) != this->_physics_accessors.end())
    {
        THROW_RUNTIME_ERROR("Cannot track two objects with the same name.");
    }

    this->_physics_accessors[name] = body;
}

void PhysicsWorld::track_rigid_body_with_name(btRigidBody* body, std::string&& name)
{
    if (this->_physics_accessors.find(name) != this->_physics_accessors.end())
    {
        THROW_RUNTIME_ERROR("Cannot track two objects with the same name.");
    }

    this->_physics_accessors[name] = body;
}

size_t PhysicsWorld::get_collision_object_count()
{
    return this->_dynamics_world->getNumCollisionObjects();
}
