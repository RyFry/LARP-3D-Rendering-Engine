#pragma once

#include "Entity.hpp"
#include "Model.hpp"
#include "Time.hpp"

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
	1.5         //1.5 units of time between frames, for either waiting or interpolating
	0           //Use model.obj; index 0 of frames
	1           //Use model1.obj; index 1 of frames
	2			//Use model2.obj; index 2 of frames

	animation2  //And so on and so forth...
	3
	1.5
	2
	1
	0

	animation3
	2
	1.5
	0
	1

	************/

	//The animation struct used to store information read from animation files
	struct Animation {
		//Construct with a name
		Animation(std::string name = "New Animation")
		{
			_name = name;
		}

		std::string _name;					   //The name of the animation
		std::vector<Model*> _frame_sequence; //A vector containing all keyframes of the animation in order
		GLfloat _frame_duration;			   //The amount of time that should pass between each keyframe
	};

	/*This class handles animations on an entity. Animations are read from special files whose format
	is described above. A LARP animation is composed of animation "frames" which are individual .obj
	files that can be cycled in rapid succession to give the appearance of natural motion. The animation
	handler can organize these frames and make sure that they cycle at a consistent rate. It can also allow
	for multiple animations to be constructed from the same set of frames.*/
	
	class AnimationHandler
	{

	public:
		AnimationHandler(Entity* ent, std::string path); /*Constructs an animation handler to use on an entity
														   from an animation file*/

		void play(std::string name, bool revert_at_end, int loop); //Plays an animation

		void stop(bool revert);				//Stop the current animation

		void update(GLfloat frame_time);					//Updates the animation handler

		std::string get_current_animation(void);

		static void update_animations();	/*Static void used to update every animation in _active_handlers;
											called in every cycle in the main while loop*/
	private:
		Entity* _entity;				    //The entity being handled

		std::vector<Model*> _frames;      //All possible frames of animation

		std::vector<Animation> _animations; //All possible animations

		GLfloat _frame_start_time;          //The time that the last animation frame played

		Animation _current_animation;       //The current animation being played

		int _loop; 							/*The loop status of the current animation;
											0 means stop the animation after the current
											cycle, more than 0 means how many more times to play
											the animation after the current cycle, -1 means
											loop infinitely until stop() is called externally*/

		unsigned int _current_frame_index;			/*The index of the current animation frame in the current
											animation's _frame_sequence array*/

		bool _animation_playing;			//Is an animation playing?

		bool _revert;						/*After all loop cycles of the current animation stop,
											should the entity be frozen at the last frame of the
											animation, or should the entity revert to the first
											frame in _frames?*/

		static std::vector<AnimationHandler*> _active_handlers; //Static vector containing all active animation handlers
	};
}
