#pragma once

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

#include "Larp/Model.hpp"
#include "Larp/Node.hpp"

namespace Physics
{
    class MeshCollider
    {
    private:
        btRigidBody* m_rigid_body;

    public:
        MeshCollider(Larp::Model* model, glm::quat rotation, glm::vec3 position,
                            GLfloat mass, glm::vec3 local_inertia, GLfloat restitution,
                            Larp::Node* user_pointer);
        btRigidBody* get_rigid_body() const;
    };
}
