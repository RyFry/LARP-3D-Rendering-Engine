#include AnimationHandler.hpp
#include <cassert>

#define NEXT_LINE assert(!animation_file.eof); \
			      std::getline(animation_file, line);

namespace Larp
{
	AnimationHandler::AnimationHandler(EntityPtr ent, std::string path)
	{
		_entity = ent;
		std::ifstream animation_file;
		animation_file.open(path);

		std::string line;
		Animation a;
		int animations;
		int frames;

		NEXT_LINE
		while(line != "")
		{
			_frames.push_back(Model::create(line));
			NEXT_LINE
		}
		NEXT_LINE
		animations = first_char_to_num(line);
		NEXT_LINE
		for(unsigned int i = 0; i < animations; ++i)
		{
			NEXT_LINE
			a(line);
			NEXT_LINE
			frames = first_char_to_num(line);
			for(unsigned int j = 0; j < frames; ++j)
			{
				NEXT_LINE
				a._frame_sequence.push_back(_frames[first_char_to_num(line)]);
				NEXT LINE
				if(j < frames - 1)
				{
					GLfloat f = std::stof(line);
					a._durations.push_back(f);
				}
			}
			NEXT_LINE
		}
	}

	static int AnimationHandler::first_char_to_num(std::string s)
	{
		return s.at(0) - '0';
	}
}