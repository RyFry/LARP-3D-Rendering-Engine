#include <string>

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
            Larp::Node* parent_node,
            GLfloat pitch, GLfloat yaw, GLfloat z,
            bool automatic);

    void initiate_physics(PhysicsWorld* world);

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
