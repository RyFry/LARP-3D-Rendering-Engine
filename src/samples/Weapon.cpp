#include "Weapon.hpp"

Weapon::Weapon(std::string default_model_path,
               std::string anim_path,
               std::string ammo_path,
               std::string sound,
               Larp::Node* parent_node,
               GLfloat pitch, GLfloat yaw, GLfloat z,
               bool automatic)
{
    Larp::Model* default_model = Larp::Model::create(default_model_path);
    m_entity = Larp::Entity::create(default_model);
    m_entity->set_directional_shadows(true);
    m_animation = new Larp::AnimationHandler(m_entity, anim_path);
    m_node = parent_node->create_child();
    m_node->attach_entity(m_entity);
    m_offset_pitch = pitch;
    m_offset_yaw = yaw;
    m_offset_z = z;
    m_ammo = ammo_path;
    m_sound = sound;
    m_auto = automatic;
}

void Weapon::initiate_physics(Physics::World* world)
{
    Physics::ObjectBuilder<btBoxShape> gun_builder;
    glm::quat gun_rot(0, 0, 0, 1);
    gun_rot = glm::rotate(gun_rot, 90.0, glm::vec3(1, 0, 0));
    m_node->set_orientation(gun_rot);
    gun_builder.set_orientation(gun_rot);
    gun_builder.set_position(m_node->get_position());
    gun_builder.set_mass(1.0);
    gun_builder.set_restitution(0.0);
    gun_builder.set_user_pointer(m_node);
    Physics::Box* gun_collider = gun_builder.build();
    btRigidBody* rigidbody = gun_collider->get_rigid_body();
    world->get_dynamics_world()->addRigidBody(rigidbody);
}
