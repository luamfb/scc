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

#include <SDL.h>
#include "config.hpp"
#include "cstylealloc.hpp"
#include "rwops.hpp"
using SDL::RWops;
#include "surface.hpp"
using SDL::Surface;

#ifdef HAVE_SDL_TTF
# include <SDL_ttf.h>
# include "truetypefont.hpp"
using SDL::TrueTypeFont;
#endif

Surface::Surface(const char *bitmapPath) : Surface(RWops(bitmapPath, "rb"))
{}

Surface::Surface(const RWops &bitmap)
	: surface_{FromRWops<Surface::Deleter>::load(bitmap, SDL_LoadBMP_RW,
		"Making surface from bitmap failed")}
{}

#ifdef HAVE_SDL_TTF
Surface::Surface(const char *text, TrueTypeFont &font, SDL_Color color)
	: surface_{CStyleAlloc<Surface::Deleter>::alloc(TTF_RenderText_Solid,
		"Making surface from text failed", font.font_.get(), text,
		color)}
{}
#endif

Surface & Surface::operator=(Surface that)
{
	swap(*this, that);
	return *this;
}

namespace SDL {

void swap(Surface &first, Surface &second) noexcept
{
	using std::swap;
	swap(first.surface_, second.surface_);
}

int blit(Surface &src, Surface &dest, const SDL_Rect *srcRect,
	SDL_Rect *destRect)
{
	return SDL_BlitSurface(src.surface_.get(), srcRect,
		dest.surface_.get(), destRect);
}

} // namespace SDL
