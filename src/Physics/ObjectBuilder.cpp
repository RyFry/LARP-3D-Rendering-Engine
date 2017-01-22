#include "ObjectBuilder.hpp"

namespace Physics
{
    template <typename BulletShape>
    ObjectBuilder<BulletShape>::ObjectBuilder()
        : m_orientation(0.0, 0.0, 0.0, 1.0),
          m_position(0.0, 0.0, 0.0),
          m_mass(0.0),
          m_local_inertia(1.0, 1.0, 1.0),
          m_restitution(1.0),
          m_user_pointer(nullptr)
    {
    }

    template <typename BulletShape>
    void ObjectBuilder<BulletShape>::set_orientation(glm::quat orientation)
    {
        m_orientation.x = orientation.x;
        m_orientation.y = orientation.y;
        m_orientation.z = orientation.z;
        m_orientation.w = orientation.w;
    }

    template <typename BulletShape>
    void ObjectBuilder<BulletShape>::set_position(glm::vec3 position)
    {
        m_position.x = position.x;
        m_position.y = position.y;
        m_position.z = position.z;
    }

    template <typename BulletShape>
    void ObjectBuilder<BulletShape>::set_mass(GLfloat mass)
    {
        m_mass = mass;
    }

    template <typename BulletShape>
    void ObjectBuilder<BulletShape>::set_local_inertia(glm::vec3 local_inertia)
    {
        m_local_inertia.x = local_inertia.x;
        m_local_inertia.y = local_inertia.y;
        m_local_inertia.z = local_inertia.z;
    }

    template <typename BulletShape>
    void ObjectBuilder<BulletShape>::set_restitution(GLfloat restitution)
    {
        m_restitution = restitution;
    }

    template <typename BulletShape>
    void ObjectBuilder<BulletShape>::set_user_pointer(Larp::Node* user_pointer)
    {
        m_user_pointer = user_pointer;
    }

    template <typename BulletShape>
    Object<BulletShape>* ObjectBuilder<BulletShape>::build()
    {
        return new Object<BulletShape>(
            m_orientation,
            m_position,
            m_mass,
            m_local_inertia,
            m_restitution,
            m_user_pointer);
    }

    template class ObjectBuilder<btBoxShape>;
// template class ObjectBuilder<btCapsuleShape>;
    template class ObjectBuilder<btCylinderShape>;
}
