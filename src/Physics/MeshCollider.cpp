#include "MeshCollider.hpp"

namespace Physics
{
    MeshCollider::MeshCollider(Larp::Model* model, glm::quat rotation,
                                      glm::vec3 position, GLfloat mass, glm::vec3 local_inertia,
                                      GLfloat restitution, Larp::Node* user_pointer)
    {
        // Make the triangle mesh based on the Model's mesh
        const std::vector<Larp::Mesh>& meshes = model->get_meshes();
        btTriangleMesh* triangle_mesh = new btTriangleMesh();

        /**
         * For each mesh in the model, we need to grab each face
         * in that mesh. The faces are defined in mesh.m_indices,
         * which has a face defined for every 3 indices, and each
         * of the indices point to a Vertex in mesh.m_vertices
         */
        glm::vec3 scale = user_pointer->get_scale();
        for (auto& mesh : meshes)
        {
            for (size_t i = 0; i < mesh.m_indices.size(); i += 3)
            {
                const Larp::Vertex& v1 = mesh.m_vertices.at(mesh.m_indices.at(i));
                const Larp::Vertex& v2 = mesh.m_vertices.at(mesh.m_indices.at(i + 1));
                const Larp::Vertex& v3 = mesh.m_vertices.at(mesh.m_indices.at(i + 2));

                triangle_mesh->addTriangle(
                    btVector3(v1.m_position.x * scale.x, v1.m_position.y * scale.y, v1.m_position.z * scale.z),
                    btVector3(v2.m_position.x * scale.x, v2.m_position.y * scale.y, v2.m_position.z * scale.z),
                    btVector3(v3.m_position.x * scale.x, v3.m_position.y * scale.y, v3.m_position.z * scale.z));
            }
        }

        btVector3 origin(position.x, position.y, position.z);
        btQuaternion orientation(rotation.w, rotation.x, rotation.y, rotation.z);

        btBvhTriangleMeshShape* mesh_shape = new btBvhTriangleMeshShape(triangle_mesh, true);
        btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(orientation, origin));

        btVector3 inertia(local_inertia.x, local_inertia.y, local_inertia.z);
        mesh_shape->calculateLocalInertia(mass, inertia);

        btVector3 li(local_inertia.x, local_inertia.y, local_inertia.z);
        btRigidBody::btRigidBodyConstructionInfo rigid_body_info(mass, motion_state, mesh_shape, li);
        m_rigid_body = new btRigidBody(rigid_body_info);
        m_rigid_body->setRestitution(restitution);
        m_rigid_body->setUserPointer(user_pointer);
    }

    btRigidBody* MeshCollider::get_rigid_body() const
    {
        return m_rigid_body;
    }

}
