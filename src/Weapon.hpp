#include <string>

#include <GLFW/glfw3.h>

#include "Larp/LarpPrerequisites.hpp"
#include "Larp/AnimationHandler.hpp"
#include "Larp/Model.hpp"
#include "Larp/Node.hpp"
#include "Larp/Entity.hpp"

struct Weapon {
	Weapon (std::string default_model_path, std::string anim_path, Larp::NodePtr parent_node)
	{
		Larp::ModelPtr default_model = Larp::Model::create(default_model_path);
		_entity = Larp::Entity::create(default_model);
		_entity->set_directional_shadows(true);
		_animation = new Larp::AnimationHandler(_entity, anim_path);
		_node = parent_node->create_child();
    	_node->attach_entity(_entity);

	}

	Larp::Node* _node;
	Larp::AnimationHandler* _animation;
	Larp::Entity* _entity;
};