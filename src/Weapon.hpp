#include <string>

#include <GLFW/glfw3.h>

#include "Larp/LarpPrerequisites.hpp"
#include "Larp/AnimationHandler.hpp"
#include "Larp/Model.hpp"
#include "Larp/Node.hpp"
#include "Larp/Entity.hpp"

#include "Physics/PhysicsMeshColliderBuilder.hpp"
#include "Physics/PhysicsObjectBuilder.hpp"

struct Weapon {
    Weapon (std::string default_model_path,
            std::string anim_path,
            std::string ammo_path,
            std::string sound,
            Larp::NodePtr parent_node,
            GLfloat pitch, GLfloat yaw, GLfloat z,
            bool automatic)
        {
            Larp::ModelPtr default_model = Larp::Model::create(default_model_path);
            _entity = Larp::Entity::create(default_model);
            _entity->set_directional_shadows(true);
            _animation = new Larp::AnimationHandler(_entity, anim_path);
            _node = parent_node->create_child();
            _node->attach_entity(_entity);
            _offset_pitch = pitch;
            _offset_yaw = yaw;
            _offset_z = z;
            _ammo = ammo_path;
            _sound = sound;
            _auto = automatic;
        }

    void initiate_physics(PhysicsWorld* world)
        {
            PhysicsObjectBuilder<btBoxShape> gun_builder;
            glm::quat gun_rot(0, 0, 0, 1);
            gun_rot = glm::rotate(gun_rot, 90.0, glm::vec3(1, 0, 0));
            _node->set_orientation(gun_rot);
            gun_builder.set_orientation(gun_rot);
            gun_builder.set_position(_node->get_position());
            gun_builder.set_mass(1.0);
            gun_builder.set_restitution(0.0);
            gun_builder.set_user_pointer(_node);
            PhysicsBoxPtr gun_collider = gun_builder.build();
            btRigidBody* rigidbody = gun_collider->get_rigid_body();
            world->get_dynamics_world()->addRigidBody(rigidbody);
        }

    GLfloat _offset_pitch;
    GLfloat _offset_yaw;
    GLfloat _offset_z;
    Larp::Node* _node;
    Larp::AnimationHandler* _animation;
    Larp::Entity* _entity;
    std::string _ammo;
    std::string _sound;
    bool _auto;
};
