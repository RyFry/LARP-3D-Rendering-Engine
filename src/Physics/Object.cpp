#include "Object.hpp"

namespace Physics
{
    template <typename BulletShape>
    Object<BulletShape>::Object(glm::quat rotation, glm::vec3 position,
                                GLfloat mass, glm::vec3 local_inertia, GLfloat restitution,
                                Larp::Node* user_pointer)
    {
        btTransform transform;
        transform.setIdentity();
        transform.setOrigin(btVector3(position.x, position.y, position.z));
        transform.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));

        btScalar bt_mass(mass);
        btVector3 inertia(local_inertia.x, local_inertia.y, local_inertia.z);

        btCollisionShape* shape = new BulletShape(btVector3(user_pointer->get_scaled_width() * 0.5,
                                                            user_pointer->get_scaled_height() * 0.5,
                                                            user_pointer->get_scaled_depth() * 0.5));
        btDefaultMotionState* motion_state = new btDefaultMotionState(transform);

        shape->calculateLocalInertia(bt_mass, inertia);

        btRigidBody::btRigidBodyConstructionInfo rigid_body_info(bt_mass, motion_state,
                                                                 shape, inertia);

        m_rigid_body = new btRigidBody(rigid_body_info);
        m_rigid_body->setRestitution(restitution);
        m_rigid_body->setUserPointer(user_pointer);
    }

    template <typename BulletShape>
    btRigidBody* Object<BulletShape>::get_rigid_body() const
    {
        return m_rigid_body;
    }

    template class Object<btBoxShape>;
    template class Object<btCylinderShape>;
}
