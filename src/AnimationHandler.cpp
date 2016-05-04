#include "AnimationHandler.hpp"
#include <cassert>

#define NEXT_LINE assert(!animation_file.eof()); \
			      std::getline(animation_file, line);

namespace Larp
{
	std::vector<AnimationHandler*> AnimationHandler::_active_handlers;

	AnimationHandler::AnimationHandler(EntityPtr ent, std::string path)
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
		animations = (int)(line.at(0) - '0');
		NEXT_LINE
		for(unsigned int i = 0; i < animations; ++i)
		{
			NEXT_LINE
			a = Animation(line);
			NEXT_LINE
			a._frame_duration = std::stof(line);
			frames = (int)(line.at(0) - '0');
			for(unsigned int j = 0; j < frames; ++j)
			{
				NEXT_LINE
				a._frame_sequence.push_back(_frames[(int)(line.at(0) - '0')]);
			}
			NEXT_LINE
		}
		_loop = 0;
		_current_frame_index = -1;
		_animation_playing = false;
		_revert = true;
		_active_handlers.push_back(this);
	}

	void AnimationHandler::play(std::string name, bool revert_at_end = true, int loop = 0)
	{
		for(unsigned int i = 0; i < _animations.size(); ++i)
		{
			if(_animations[i]._name == name)
			{
				_current_animation = _animations[i];
				_current_frame_index = 0;
				_animation_playing = true;
				_revert = revert_at_end;
				_loop = loop;
				_entity->switch_model(_current_animation._frame_sequence[_current_frame_index]);
				_frame_start_time = Time::current_time();
			}
			std::cout << "Could not find animation" << std::endl;
		}
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

	void AnimationHandler::update()
	{
		GLfloat frame_time = Time::current_time();
		if(frame_time - _frame_start_time >= _current_animation._frame_duration)
		{
			if(_current_frame_index < _current_animation._frame_sequence.size())
			{
				++_current_frame_index;
			}
			else
			{
				if(_loop != 0)
				{
					_current_frame_index = 0;
					if(_loop != -1)
					{
						--_loop;
					}
				}
				else
				{
					stop(_revert);
					return;
				}
			}
			_entity->switch_model(_current_animation._frame_sequence[_current_frame_index]);
			_frame_start_time = Time::current_time();
		}
	}

	void AnimationHandler::update_animations()
	{
		for(unsigned int i = 0; i < _active_handlers.size(); ++i)
		{
			_active_handlers[i]->update();
		}
	}
}