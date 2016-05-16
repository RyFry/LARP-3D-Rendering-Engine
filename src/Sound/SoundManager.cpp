#include "SoundManager.hpp"

Mix_Music* SoundManager::_background_music;

std::map<std::string, Mix_Chunk*> SoundManager::_sound_effects;

float SoundManager::_effect_volume = 0.2f;
float SoundManager::_music_volume = 0.02f;
int SoundManager::_walk = 0;

SoundManager::SoundManager()
{
    
}

SoundManager::~SoundManager()
{
}

void SoundManager::sound_init()
{
    Larp::CustomConfigurationLoader* config = Larp::CustomConfigurationLoader::load_configurations("sound.cfg");
    _music_volume = std::stof(config->get_configuration("music_volume"));
    _effect_volume = std::stof(config->get_configuration("sound_volume"));

    SDL_Init(SDL_INIT_EVERYTHING);

    srand(time(NULL));

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

    /*Load sound effects here */
    _background_music = Mix_LoadMUS("assets/sound/Neotantra.mp3");
    _sound_effects.emplace("shotgun", Mix_LoadWAV("assets/sound/shotgun.wav"));
    _sound_effects.emplace("rocket_fire", Mix_LoadWAV("assets/sound/rocket_fire.wav"));
    _sound_effects.emplace("chaingun", Mix_LoadWAV("assets/sound/chaingun.wav"));
    _sound_effects.emplace("jump", Mix_LoadWAV("assets/sound/jump.wav"));
    _sound_effects.emplace("walk0", Mix_LoadWAV("assets/sound/walking0.wav"));
    _sound_effects.emplace("walk1", Mix_LoadWAV("assets/sound/walking1.wav"));

    Mix_VolumeMusic(MIX_MAX_VOLUME * _music_volume);
    Mix_Volume(-1, MIX_MAX_VOLUME * _effect_volume);
}

void SoundManager::sound_quit()
{
    SDL_CloseAudio();
    SDL_Quit();
}

void SoundManager::play_sound(std::string effectName)
{

    if(effectName == "walk")
    {
        if (Mix_Playing(0))
            return;
        std::string temp(effectName + std::to_string(_walk));
        if(_walk == 0)
        {
            Mix_PlayChannel(0, _sound_effects.at(temp), 0);
            ++_walk;
        }
        else
        {
            Mix_PlayChannel(0, _sound_effects.at(temp), 0);
            --_walk;
        }
    }
    else if(effectName == "jump")
    {
        if (Mix_Playing(1))
            return;
        Mix_PlayChannel(1, _sound_effects.at(effectName.c_str()), 0);
    }
    else
    {
        Mix_PlayChannel(-1, _sound_effects.at(effectName.c_str()), 0);
    }
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
