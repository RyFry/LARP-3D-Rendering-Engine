#include "AnimationHandler.hpp"
#include <cassert>

#define NEXT_LINE assert(!animation_file.eof()); \
			      std::getline(animation_file, line);

namespace Larp
{
	std::vector<AnimationHandler*> AnimationHandler::s_active_handlers;

	AnimationHandler::AnimationHandler(Entity* ent, std::string path)
	{
		m_entity = ent;
		std::ifstream animation_file;
		animation_file.open(path);

		std::string line;
		Animation a;
		unsigned int animations;
		unsigned int frames;

		NEXT_LINE
		while(line != "")
		{
			m_frames.push_back(Model::create(line));
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
			a.m_frame_duration = std::stof(line);
			// std::cout << "Animation frame duration is " << std::stof(line) << " seconds." << std::endl;
			for(unsigned int j = 0; j < frames; ++j)
			{
				NEXT_LINE
				a.m_frame_sequence.push_back(m_frames[std::stoi(line)]);
			}
			m_animations.push_back(a);
			NEXT_LINE
		}
		m_current_animation = m_animations[0];
		m_loop = 0;
		m_current_frame_index = -1;
		m_animation_playing = false;
		m_revert = true;
		s_active_handlers.push_back(this);
	}

	void AnimationHandler::play(std::string name, bool revert_at_end, int loop)
	{
		// std::cout << "Called play!" << std::endl;
		// std::cout << "There are " << m_animations.size() << " animations." << std::endl;
		for(unsigned int i = 0; i < m_animations.size(); ++i)
		{
			// std::cout << "Searching for animation, i = " << i << std::endl;
			if(m_animations[i].m_name == name)
			{
				// std::cout << "Found animation named " << m_animations[i].m_name << std::endl;
				m_current_animation = m_animations[i];
				m_current_frame_index = 0;
				m_animation_playing = true;
				m_revert = revert_at_end;
				m_loop = loop;
				m_entity->switch_model(m_current_animation.m_frame_sequence[m_current_frame_index]);
				m_frame_start_time = Time::current_time();
			}
		}
		// std::cout << "Could not find animation" << std::endl;
	}

	void AnimationHandler::stop(bool revert = true)
	{
		m_loop = 0;
		m_current_frame_index = -1;
		m_animation_playing = false;
		m_revert = true;
		if(revert)
		{
			m_entity->switch_model(m_frames[0]);
		}
	}

	void AnimationHandler::update(GLfloat frame_time)
	{
		if(frame_time - m_frame_start_time >= m_current_animation.m_frame_duration && m_animation_playing)
		{

			// std::cout << "Updating an animation! We're playing " << m_current_animation.m_name << std::endl;
			// std::cout << "Current frame time is " << frame_time - m_frame_start_time << ", needs to be " << m_current_animation.m_frame_duration << std::endl;
			// std::cout << "Current frame index is " << m_current_frame_index << " and there are " << m_current_animation.m_frame_sequence.size() << " frames." << std::endl;
			m_entity->switch_model(m_current_animation.m_frame_sequence[m_current_frame_index]);
			// std::cout << "I just switched a model." << std::endl;
			if(m_current_frame_index < m_current_animation.m_frame_sequence.size() - 1)
			{
				++m_current_frame_index;
			}
			else
			{
				// std::cout << "Current value of loop: " << m_loop << std::endl;
				if(m_loop != 0)
				{
					m_current_frame_index = 0;
					if(m_loop != -1)
					{
						--m_loop;
					}
					// std::cout << "Reverting to start of animation loop!" << std::endl;
				}
				else
				{
					stop(m_revert);
					// std::cout << "Animation stopped!" << std::endl;
					return;
				}
			}
			m_frame_start_time = Time::current_time();
		}
	}

	std::string AnimationHandler::get_current_animation()
	{
		if(!m_animation_playing)
		{
			return "NO ANIMATION PLAYING";
		}
		else
		{
			return m_current_animation.m_name;
		}
	}

	void AnimationHandler::update_animations()
	{
		for(unsigned int i = 0; i < s_active_handlers.size(); ++i)
		{
			s_active_handlers[i]->update(Time::current_time());
		}
	}
}
