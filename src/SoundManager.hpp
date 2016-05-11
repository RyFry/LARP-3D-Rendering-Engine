#pragma once


#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string.h>
#include <map>

#include "Larp/LarpPrerequisites.hpp"
#include "Larp/ConfigurationLoader.hpp"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
	
class SoundManager
{
		public:
			SoundManager();
			~SoundManager();

			static void sound_init();

			static void sound_quit();

			static void play_sound(const char* effectName);

			static void play_music();

			static void mute_music();

			static void effect_change_volume(const float vol);

			static void music_change_volume(const float vol);
			

		private:
			
						
			static Mix_Music* _background_music;

			static std::map<std::string, Mix_Chunk*> _sound_effects;

			static float _effect_volume;
			
			static float _music_volume;

			static int _walk;


};
