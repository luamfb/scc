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
#include "window.hpp"
#include "surface.hpp"

const int ERR_SDL_INIT = -1;
using SDL::Window;
using SDL::Surface;

bool init(Uint32 sdlInitFlags)
{
	return SDL_Init(sdlInitFlags) == 0;
}

void quit()
{
	SDL_Quit();
}

void gameLoop()
{
	Window window("test");
	Surface surface = Surface::fromBitmap("screen.bmp");

	bool quit = false;
	while(!quit) {
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				quit = true;
			}
		}

		// I hope you enjoy this, because I don't think your CPU will.
	
		if(!blitScaled(surface, window.getSurface()))
		{
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
				"failed blitting to window's surface!");
			return;
		}
		if(!window.updateSurface())
		{
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
				"failed updating window surface!");
			return;
		}
		SDL_Delay(10); // CPU usage skyrockets without this
	}
}

int main(int argc, char **argv)
{
	if(!init(SDL_INIT_VIDEO)) {
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
			"couldn't initialize SDL\n");
		return ERR_SDL_INIT;
	}
	gameLoop();
	quit();
	return 0;
}
