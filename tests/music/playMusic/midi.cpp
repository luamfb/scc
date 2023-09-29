/*
  SDL C++ Classes
  Copyright (C) 2017-2018 Luana Carmo M. de F. Barbosa
 
  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.
 
  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:
 
  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <SDL.h>
#include <SDL_mixer.h>
#include "common.hpp"

const char *filename = "song.mid";
const int ERR_SDL_INIT = -1;

// FIXME
// 1) pressing 'p' only works the first time
// 2) reusming after halting gives a weird sound as if the music was stuck
// 3) rewinding doesn't work
int main(int argc, char **argv)
{
	Uint32 sdlFlags = SDL_INIT_VIDEO | SDL_INIT_AUDIO;
	int mixerFlags = MIX_INIT_FLUIDSYNTH;
	if(!init(sdlFlags, mixerFlags)) {
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
			"couldn't initialize SDL: %s\n", SDL_GetError());
		return ERR_SDL_INIT;
	}
	test(filename, MUS_MID);
	quit();
	return 0;
}
