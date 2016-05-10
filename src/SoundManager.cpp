#include "SoundManager.hpp"

Mix_Music* SoundManager::_background_music;

std::map<std::string, Mix_Chunk*> SoundManager::_sound_effects;

float SoundManager::_effect_volume;
			
float SoundManager::_music_volume;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::sound_init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	srand(time(NULL));

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

	/*Load sound effects here */
}

void SoundManager::sound_quit()
{
	SDL_CloseAudio();
	SDL_Quit();
}

void SoundManager::play_sound(const char* effectName)
{
	Mix_PlayChannel(-1, _sound_effects.at(effectName), 0);
}
void SoundManager::play_music()
{
	Mix_PlayMusic(_background_music, -1);
}

void SoundManager::mute_music()
{
	if(Mix_VolumeMusic(-1) == 0)
		Mix_VolumeMusic(MIX_MAX_VOLUME * _music_volume);
	else
		Mix_VolumeMusic(0);
}

void SoundManager::effect_change_volume(const float vol)
{
	Mix_Volume(-1, MIX_MAX_VOLUME * vol);
	_effect_volume = vol;
}	

void SoundManager::music_change_volume(const float vol)
{
	Mix_VolumeMusic(MIX_MAX_VOLUME * vol);
	_music_volume = vol;

}