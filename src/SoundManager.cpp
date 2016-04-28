#include "SoundManager.hpp"

SoundManager::SoundManager()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	srand(time(NULL));
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	


}

SoundManager::~SoundManager()
{

}