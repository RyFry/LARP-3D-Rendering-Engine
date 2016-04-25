#include "PhysicsMeshCollider.hpp"

PhysicsMeshCollider::PhysicsMeshCollider(Larp::ModelPtr model, btQuaternion rotation,
                                         btVector3 position, btScalar mass, btVector3 local_inertia,
                                         btScalar restitution, void * user_pointer)
{
    // Make the triangle mesh based on the Model's mesh
    const std::vector<Larp::Mesh>& meshes = model->get_meshes();
    btTriangleMesh* triangle_mesh = new btTriangleMesh();

    /**
     * For each mesh in the model, we need to grab each face
     * in that mesh. The faces are defined in mesh._indices,
     * which has a face defined for every 3 indices, and each
     * of the indices point to a Vertex in mesh._vertices
     */
    for (auto& mesh : meshes)
    {
        for (size_t i = 0; i < mesh._indices.size(); i += 3)
        {
            const Larp::Vertex& v1 = mesh._vertices.at(mesh._indices.at(i));
            const Larp::Vertex& v2 = mesh._vertices.at(mesh._indices.at(i + 1));
            const Larp::Vertex& v3 = mesh._vertices.at(mesh._indices.at(i + 2));

            triangle_mesh->addTriangle(
                btVector3(v1._position.x, v1._position.y, v1._position.z),
                btVector3(v2._position.x, v2._position.y, v2._position.z),
                btVector3(v3._position.x, v3._position.y, v3._position.z));
        }
    }

    btBvhTriangleMeshShape* mesh_shape = new btBvhTriangleMeshShape(triangle_mesh, true);
    btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(rotation, position));

    mesh_shape->calculateLocalInertia(mass, local_inertia);

    btRigidBody::btRigidBodyConstructionInfo rigid_body_info(mass, motion_state, mesh_shape, local_inertia);
    this->_rigid_body = new btRigidBody(rigid_body_info);
    this->_rigid_body->setRestitution(restitution);
    this->_rigid_body->setUserPointer(user_pointer);
}

btRigidBody* PhysicsMeshCollider::get_rigid_body() const
{
    return this->_rigid_body;
}
