#include "SoundManager.hpp"


SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void sound_init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	srand(time(NULL));

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

	/*Load sound effects here */
}

void sound_quit()
{
	SDL_CloseAudio();
	SDL_Quit();
}

void play_sound(const std::string effectName)
{
	Mix_PlayChannel(-1, this->_sound_effects.at(effectName), 0);
}
void play_music()
{
	Mix_PlayMusic(this->_music, -1);
}

void mute_music()
{
	if(Mix_VolumeMusic(-1) == 0)
		Mix_VolumeMusic(MIX_MAX_VOLUME * this->_music_volume);
	else
		Mix_VolumeMusic(0);
}

void effect_change_volume(const float vol)
{
	Mix_Volume(-1, MIX_MAX_VOLUME * vol);
	this->_effect_volume = vol;
}	

void music_change_volume(const float vol)
{
	Mix_VolumeMusic(MIX_MAX_VOLUME * vol);
	this->_music_volume = vol;

}