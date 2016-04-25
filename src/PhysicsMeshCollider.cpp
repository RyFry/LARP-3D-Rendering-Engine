#include "PhysicsMeshCollider.hpp"

PhysicsMeshCollider(ModelPtr model, btQuaternion rotation, btPosition position,
                    btScalar mass, btVector3 local_intertia, btScalar restitution)
{
    // Make the triangle mesh based on the Model's mesh
    const std::vector<Mesh>& meshes = model->get_meshes();
    btTriangleMesh* triangle_mesh = new btTriangleMesh();

    for (auto& mesh : meshes)
    {
        for (auto& vertex : mesh._vertices)
        {
            
        }
    }
}
