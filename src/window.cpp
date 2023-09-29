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

#include <memory>
#include <SDL.h>
#include "cstylealloc.hpp"
#include "renderer.hpp"
#include "window.hpp"

using SDL::Renderer;
using SDL::Window;

Window::Window(const char *title, int width, int height, int x, int y,
	Uint32 flags)
	: window_{CStyleAlloc<Window::Deleter>::alloc(SDL_CreateWindow,
		"Making window failed", title, x, y, width, height, flags)}
{}

Window & Window::operator=(Window that)
{
	swap(*this, that);
	return *this;
}

namespace SDL {

void swap(Window &first, Window &second) noexcept
{
	using std::swap;
	swap(first.window_, second.window_);
}

} // namespace SDL

void Window::getSize(int *width, int *height) const
{
	SDL_GetWindowSize(window_.get(), width, height);
}

int Window::getWidth() const
{
	int width;
	SDL_GetWindowSize(window_.get(), &width, NULL);
	return width;
}

int Window::getHeight() const
{
	int height;
	SDL_GetWindowSize(window_.get(), NULL, &height);
	return height;
}
