#include "PhysicsObjectBuilder.hpp"

template <typename T>
PhysicsObjectBuilder<T>::PhysicsObjectBuilder()
    : _orientation(0.0, 0.0, 0.0, 1.0),
      _position(0.0, 0.0, 0.0),
      _mass(0.0),
      _local_inertia(0.0, 0.0, 0.0),
      _restitution(1.0),
      _user_pointer(nullptr)
{
}

template <typename T>
void PhysicsObjectBuilder<T>::set_orientation(glm::quat orientation)
{
    this->_orientation.x = orientation.x;
    this->_orientation.y = orientation.y;
    this->_orientation.z = orientation.z;
    this->_orientation.w = orientation.w;
}

template <typename T>
void PhysicsObjectBuilder<T>::set_position(glm::vec3 position)
{
    this->_position.x = position.x;
    this->_position.y = position.y;
    this->_position.z = position.z;
}

template <typename T>
void PhysicsObjectBuilder<T>::set_mass(GLfloat mass)
{
    this->_mass = mass;
}

template <typename T>
void PhysicsObjectBuilder<T>::set_local_inertia(glm::vec3 local_inertia)
{
    this->_local_inertia.x = local_inertia.x;
    this->_local_inertia.y = local_inertia.y;
    this->_local_inertia.z = local_inertia.z;
}

template <typename T>
void PhysicsObjectBuilder<T>::set_restitution(GLfloat restitution)
{
    this->_restitution = restitution;
}

template <typename T>
void PhysicsObjectBuilder<T>::set_user_pointer(Larp::NodePtr user_pointer)
{
    this->_user_pointer = user_pointer;
}

template <typename T>
PhysicsObject<T>* PhysicsObjectBuilder<T>::build()
{
    return new PhysicsObject<T>(_orientation, _position, _mass, _local_inertia,
                                _restitution, _user_pointer);
}

template class PhysicsObjectBuilder<btBoxShape>;
// template class PhysicsObjectBuilder<btCapsuleShape>;
template class PhysicsObjectBuilder<btCylinderShape>;
