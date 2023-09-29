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
#ifndef SCC_HPP
#define SCC_HPP

#include "versioncheck.hpp"
#include "config.hpp"

#ifdef HAVE_SDL_TTF
# include "truetypefont.hpp"
#endif

#ifdef HAVE_SDL_MIXER
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
