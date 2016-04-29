#include "Entity.hpp"
#include "Model.hpp"

namespace Larp
{
	/*sample animation file (don't put comments or asterisks in the actual file!):
	************
	model.obj   //Define all model paths; the first model is the one that will be used when no animation is playing  
	model1.obj
	model2.obj
                //Don't forget blank lines!
	3           //Number of animations

	animation1  //Name of first animation
	3           //Number of frames in first animation
	0           //Use model.obj; index 0 of frames
	1.5         //1.5 units of time between frames, for either waiting or interpolating
	1           //Use model1.obj; index 1 of frames
	1.5         //1.5 units of time between frames, for either waiting or interpolating
	2			//Use model2.obj; index 2 of frames

	animation2  //And so on and so forth...
	3
	2
	1.5
	1
	1.5
	0

	animation3
	2
	0
	1.5
	1

	************/
	class AnimationHandler
	{

	public:
		AnimationHandler(EntityPtr ent, std::string path);

		static void update_animations();
	private:
		EntityPtr _entity;
		std::vector<ModelPtr> _frames;
		std::vector<Animation> _animations;

		static std::vector<AnimationHandler> _active_handlers;
	};

	struct Animation {
		Animation(std::string name = "New Animation")
		{
			string_name = name;
		}

		std::string name;
		std::vector<ModelPtr> _frame_sequence;
		std::vector<GLfloat> _durations;
	};
}