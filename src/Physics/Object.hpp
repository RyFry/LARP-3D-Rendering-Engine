#pragma once

#include <btBulletDynamicsCommon.h>

#include "Larp/LarpPrerequisites.hpp"
#include "Larp/Node.hpp"
#include "World.hpp"

namespace Physics
{
    template <typename BulletShape>
    class Object
    {
    private:
        btRigidBody* m_rigid_body;
    public:
        Object(glm::quat orientation,
               glm::vec3 position,
               GLfloat mass,
               glm::vec3 local_inertia,
               GLfloat restitution,
               Larp::Node* user_pointer);
        btRigidBody* get_rigid_body() const;
    };

    typedef Object<btBoxShape> Box;
    typedef Object<btCylinderShape> Cylinder;
}
