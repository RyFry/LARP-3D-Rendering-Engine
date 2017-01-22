#pragma once

#include <string>

#include "Larp/LarpPrerequisites.hpp"
#include "Larp/Model.hpp"

#include "MeshCollider.hpp"

namespace Physics
{
    class MeshColliderBuilder
    {
    private:
        /**
         * The Model that this mesh collider will be built from.
         */
        Larp::Model* m_model;
        /**
         * The orientation of the Mesh collider that will be built.
         */
        glm::quat m_orientation;
        /**
         * The position of the Mesh collider that will be built.
         */
        glm::vec3 m_position;
        /**
         * The mas of the Mesh collider that will be built.
         */
        GLfloat m_mass;
        /**
         * The local intertia of the Mesh collider that will be built.
         */
        glm::vec3 m_local_inertia;
        /**
         * The restitution of the Mesh collider that will be built.
         * A value of 1.0 will have perfect bouncing, and a value of 0.0
         * will have no bouncing.
         */
        GLfloat m_restitution;
        /**
         * The data pointer of this Mesh collider. This should be initialized
         * to the Larp::Node* that is attached to the Model provided
         * to the Mesh collider.
         */
        Larp::Node* m_user_pointer;
    public:
        /**
         * Constructor
         * @param path The path to the Model to build a MeshCollider off of
         */
        MeshColliderBuilder(std::string path);
        /**
         * Set the orientation for the MeshCollider to be built by this object
         * @param orientation The orientation amount
         * @default (0, 0, 0, 1)
         */
        void set_orientation(glm::quat orientation);
        /**
         * Set the position for the MeshCollider to be built by this object
         * @param position The position amount
         * @default (0, 0, 0)
         */
        void set_position(glm::vec3 position);
        /**
         * Set the mass for the MeshCollider to be built by this object
         * A mass of 0.0 means that this object will not move or be affected
         * by gravity
         * @param mass The mass amount
         * @default 0.0
         */
        void set_mass(GLfloat mass);
        /**
         * Set the local inertia for the MeshCollider to be built by this object
         * @param local inertia The local inertia amount
         * @default (0, 0, 0)
         */
        void set_local_inertia(glm::vec3 local_inertia);
        /**
         * Set the restitution for the MeshCollider to be built by this object
         * @param restitution The restitution amount
         * @default 0.0
         */
        void set_restitution(GLfloat restitution);
        /**
         * Set the user pointer for the MeshCollider to be built by this object
         * @param user_pointer The user pointer amount
         * @default nullptr
         */
        void set_user_pointer(Larp::Node* user_pointer);
        MeshCollider* build();
    };
}
