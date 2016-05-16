#include "AnimationHandler.hpp"
#include <cassert>

#define NEXT_LINE assert(!animation_file.eof()); \
			      std::getline(animation_file, line);

namespace Larp
{
	std::vector<AnimationHandler*> AnimationHandler::_active_handlers;

	AnimationHandler::AnimationHandler(Entity* ent, std::string path)
	{
		_entity = ent;
		std::ifstream animation_file;
		animation_file.open(path);

		std::string line;
		Animation a;
		unsigned int animations;
		unsigned int frames;

		NEXT_LINE
		while(line != "")
		{
			_frames.push_back(Model::create(line));
			NEXT_LINE
		}
		NEXT_LINE
		animations = std::stoi(line);
		// std::cout << "Animations: " << animations << std::endl;
		NEXT_LINE
		for(unsigned int i = 0; i < animations; ++i)
		{
			// std::cout << "Animation " << i+1 << std::endl;
			NEXT_LINE
			a = Animation(line);
			// std::cout << "New animation called " << line;
			NEXT_LINE
			frames = std::stoi(line);
			// std::cout << " with " << frames << " frames." << std::endl;
			NEXT_LINE
			a._frame_duration = std::stof(line);
			// std::cout << "Animation frame duration is " << std::stof(line) << " seconds." << std::endl;
			for(unsigned int j = 0; j < frames; ++j)
			{
				NEXT_LINE
				a._frame_sequence.push_back(_frames[std::stoi(line)]);
			}
			_animations.push_back(a);
			NEXT_LINE
		}
		_current_animation = _animations[0];
		_loop = 0;
		_current_frame_index = -1;
		_animation_playing = false;
		_revert = true;
		_active_handlers.push_back(this);
	}

	void AnimationHandler::play(std::string name, bool revert_at_end, int loop)
	{
		// std::cout << "Called play!" << std::endl;
		// std::cout << "There are " << _animations.size() << " animations." << std::endl;
		for(unsigned int i = 0; i < _animations.size(); ++i)
		{
			// std::cout << "Searching for animation, i = " << i << std::endl;
			if(_animations[i]._name == name)
			{
				// std::cout << "Found animation named " << _animations[i]._name << std::endl;
				_current_animation = _animations[i];
				_current_frame_index = 0;
				_animation_playing = true;
				_revert = revert_at_end;
				_loop = loop;
				_entity->switch_model(_current_animation._frame_sequence[_current_frame_index]);
				_frame_start_time = Time::current_time();
			}
		}
		// std::cout << "Could not find animation" << std::endl;
	}

	void AnimationHandler::stop(bool revert = true)
	{
		_loop = 0;
		_current_frame_index = -1;
		_animation_playing = false;
		_revert = true;
		if(revert)
		{
			_entity->switch_model(_frames[0]);
		}
	}

	void AnimationHandler::update(GLfloat frame_time)
	{
		if(frame_time - _frame_start_time >= _current_animation._frame_duration && _animation_playing)
		{

			// std::cout << "Updating an animation! We're playing " << _current_animation._name << std::endl;
			// std::cout << "Current frame time is " << frame_time - _frame_start_time << ", needs to be " << _current_animation._frame_duration << std::endl;
			// std::cout << "Current frame index is " << _current_frame_index << " and there are " << _current_animation._frame_sequence.size() << " frames." << std::endl;
			_entity->switch_model(_current_animation._frame_sequence[_current_frame_index]);
			// std::cout << "I just switched a model." << std::endl;
			if(_current_frame_index < _current_animation._frame_sequence.size() - 1)
			{
				++_current_frame_index;
			}
			else
			{
				// std::cout << "Current value of loop: " << _loop << std::endl;
				if(_loop != 0)
				{
					_current_frame_index = 0;
					if(_loop != -1)
					{
						--_loop;
					}
					// std::cout << "Reverting to start of animation loop!" << std::endl;
				}
				else
				{
					stop(_revert);
					// std::cout << "Animation stopped!" << std::endl;
					return;
				}
			}
			_frame_start_time = Time::current_time();
		}
	}

	std::string AnimationHandler::get_current_animation()
	{
		if(!_animation_playing)
		{
			return "NO ANIMATION PLAYING";
		}
		else
		{
			return _current_animation._name;
		}
	}

	void AnimationHandler::update_animations()
	{
		for(unsigned int i = 0; i < _active_handlers.size(); ++i)
		{
			_active_handlers[i]->update(Time::current_time());
		}
	}
}
