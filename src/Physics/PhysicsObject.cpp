#include "PhysicsObject.hpp"

template <typename BulletShape>
PhysicsObject<BulletShape>::PhysicsObject(glm::quat rotation, glm::vec3 position,
                                          GLfloat mass, glm::vec3 local_inertia, GLfloat restitution,
                                          Larp::NodePtr user_pointer)
{
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(position.x, position.y, position.z));
    transform.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));

    btScalar bt_mass(mass);
    btVector3 inertia;

    btCollisionShape* shape = new BulletShape(btVector3(user_pointer->get_scaled_width(),
                                                        user_pointer->get_scaled_height(),
                                                        user_pointer->get_scaled_depth()));
    btDefaultMotionState* motion_state = new btDefaultMotionState(transform);

    shape->calculateLocalInertia(bt_mass, inertia);

    btRigidBody::btRigidBodyConstructionInfo rigid_body_info(bt_mass, motion_state,
                                                             shape, inertia);
    rigid_body_info.m_linearDamping = .2f;
    rigid_body_info.m_angularDamping = .2f;
    this->_rigid_body = new btRigidBody(rigid_body_info);
    this->_rigid_body->setRestitution(restitution);
    this->_rigid_body->setUserPointer(user_pointer);
    this->_rigid_body->setFriction(.5f);
    this->_rigid_body->setRollingFriction(.5f);
}

template <typename BulletShape>
btRigidBody* PhysicsObject<BulletShape>::get_rigid_body() const
{
    return this->_rigid_body;
}

template class PhysicsObject<btBoxShape>;
//template class PhysicsObject<btCapsuleShape>;
template class PhysicsObject<btCylinderShape>;
