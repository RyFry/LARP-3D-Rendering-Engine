#include "World.hpp"

std::ostream& operator << (std::ostream& out, const btVector3& vec)
{
    out << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")";
    return out;
}

namespace Physics
{
    World::World()
        : m_collision_configuration(0),
          m_dispatcher(0),
          m_overlapping_pair_cache(0),
          m_solver(0),
          m_dynamics_world(0)
    {
    }

    World::~World() 
    {
        if (m_dynamics_world) delete m_dynamics_world;
        if (m_solver) delete m_solver;
        if (m_dispatcher) delete m_dispatcher;
        if (m_collision_configuration) delete m_collision_configuration;
        if (m_overlapping_pair_cache) delete m_overlapping_pair_cache;
    }

    void World::init_objects()
    {
        m_collision_configuration = new btDefaultCollisionConfiguration();
        m_dispatcher = new btCollisionDispatcher(m_collision_configuration);
        m_overlapping_pair_cache = new btDbvtBroadphase();
        m_overlapping_pair_cache->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
        m_solver = new btSequentialImpulseConstraintSolver();
        m_dynamics_world = new btDiscreteDynamicsWorld(
            m_dispatcher,
            m_overlapping_pair_cache,
            m_solver,
            m_collision_configuration);
    }

    btDiscreteDynamicsWorld* World::get_dynamics_world()
    {
        return m_dynamics_world;
    }

    std::vector<btCollisionShape *>& World::get_collision_shapes()
    {
        return m_collision_shape;
    }

    void World::track_rigid_body_with_name(btRigidBody* body, std::string& name)
    {
        if (m_physics_accessors.find(name) != m_physics_accessors.end())
        {
            THROW_RUNTIME_ERROR("Cannot track two objects with the same name.");
        }

        m_physics_accessors[name] = body;
    }

    void World::track_rigid_body_with_name(btRigidBody* body, std::string&& name)
    {
        if (m_physics_accessors.find(name) != m_physics_accessors.end())
        {
            THROW_RUNTIME_ERROR("Cannot track two objects with the same name.");
        }

        m_physics_accessors[name] = body;
    }

    size_t World::get_collision_object_count()
    {
        return m_dynamics_world->getNumCollisionObjects();
    }
}
