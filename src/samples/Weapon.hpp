#include <string>

#include "Larp/LarpPrerequisites.hpp"
#include "Larp/AnimationHandler.hpp"
#include "Larp/Model.hpp"
#include "Larp/Node.hpp"
#include "Larp/Entity.hpp"

#include "Physics/MeshColliderBuilder.hpp"
#include "Physics/ObjectBuilder.hpp"

struct Weapon
{
    Weapon (std::string default_model_path,
            std::string anim_path,
            std::string ammo_path,
            std::string sound,
            Larp::Node* parent_node,
            GLfloat pitch, GLfloat yaw, GLfloat z,
            bool automatic);

    void initiate_physics(Physics::World* world);

    GLfloat m_offset_pitch;
    GLfloat m_offset_yaw;
    GLfloat m_offset_z;
    Larp::Node* m_node;
    Larp::AnimationHandler* m_animation;
    Larp::Entity* m_entity;
    std::string m_ammo;
    std::string m_sound;
    bool m_auto;
};
