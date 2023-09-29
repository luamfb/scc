/*
  SDL C++ Classes
  Copyright (C) 2017 Luana Carmo M. de F. Barbosa
 
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

// scc.hpp: the header that pulls all others.
// Make sure to include SDL.h before this!
// If you want to use a subproject X of SDL, you must define HAVE_SDL_X
// and include its respective header as well.
#ifndef SCC_HPP
#define SCC_HPP

#if __cplusplus < 201103L
# error "at least C++11 is needed"
#endif

#if !defined(SDL_MAJOR_VERSION) || !defined(SDL_MINOR_VERSION)
# error "Could not determine the SDL version. Is SDL.h included?"
#endif

#if SDL_MAJOR_VERSION < 2
# error "at least SDL 2.0 is needed."
#endif

#ifdef HAVE_SDL_IMAGE
# ifndef SDL_IMAGE_MAJOR_VERSION
#  error "HAVE_SDL_IMAGE is defined, but SDL_image.h isn't included!"
# endif
#endif

#ifdef HAVE_SDL_TTF
# ifndef SDL_TTF_MAJOR_VERSION
#  error "HAVE_SDL_TTF is defined, but SDL_ttf.h isn't included!"
# endif
# include "truetypefont.hpp"
#endif

#ifdef HAVE_SDL_MIXER
# ifndef SDL_MIXER_MAJOR_VERSION
#  error "HAVE_SDL_MIXER is defined, but SDL_mixer.h isn't included!"
# endif
# include "audiochunk.hpp"
# include "audiochannels.hpp"
# include "music.hpp"
#endif

#include "glcontext.hpp"
#include "renderer.hpp"
#include "rwops.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include "window.hpp"

#endif
