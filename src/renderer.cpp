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
#include <vector>
#include <stdexcept>
#include <SDL.h>
#include "cstylealloc.hpp"
#include "window.hpp"
#include "renderer.hpp"

using SDL::Window;
using SDL::Renderer;

Renderer::Renderer() : renderer_{nullptr}
{}

Renderer::Renderer(SDL_Window *window, Uint32 flags)
	: renderer_{CStyleAlloc<Renderer::Deleter>::alloc(SDL_CreateRenderer,
		"Making renderer failed", window, -1, flags)}
{}

Renderer & Renderer::operator=(Renderer that)
{
	swap(*this, that);
	return *this;
}

namespace SDL {

void swap(Renderer &first, Renderer &second) noexcept
{
	using std::swap;
	swap(first.renderer_, second.renderer_);
}

} // namespace SDL

void Renderer::present()
{
	SDL_RenderPresent(renderer_.get());
}

void Renderer::clear()
{
	SDL_RenderClear(renderer_.get());
}

void Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(renderer_.get(), r, g, b, a);
}

void Renderer::render(Texture &texture, int x, int y) const
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	texture.query(NULL, NULL, &dest.w, &dest.h);

	// NULL for the entire texture
	SDL_RenderCopy(renderer_.get(), texture.texture_.get(), NULL, &dest);
}

void Renderer::render(Texture &texture, const SDL_Rect *src,
	const SDL_Rect *dest) const
{
	SDL_RenderCopy(renderer_.get(), texture.texture_.get(), src, dest);
}

bool Renderer::setTarget(Texture &texture) const
{
	return setTarget(texture.texture_.get());
}

bool Renderer::setTarget(SDL_Texture *texture) const
{
	// "Before using this function, you should check the
	// SDL_RENDERER_TARGETTEXTURE bit in the flags of SDL_RendererInfo to
	// see if render targets are supported."
	// (<wiki.libsdl.org/SDL_SetRenderTarget>)
	// Well, here it is
	if((getInfo().flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
		SDL_SetError("renderer can't use texture as target");
		return false;
	}
	// so it works with nullptr too
	if(texture == nullptr) {
		texture = NULL;
	}
	return SDL_SetRenderTarget(renderer_.get(), texture) >= 0;
}

SDL_RendererInfo Renderer::getInfo() const
{
	SDL_RendererInfo info;
	SDL_GetRendererInfo(renderer_.get(), &info);
	return info;
}

bool Renderer::drawPoint(int x, int y) const
{
	return SDL_RenderDrawPoint(renderer_.get(), x, y) >= 0;
}

bool Renderer::drawPoints(const std::vector<SDL_Point> points) const
{
	if(points.empty()) {
		return false;
	}
	return SDL_RenderDrawPoints(renderer_.get(), points.data(),
		points.size()) >= 0;
}

bool Renderer::drawLine(int x1, int y1, int x2, int y2) const
{
	return SDL_RenderDrawLine(renderer_.get(), x1, y1, x2, y2);
}

bool Renderer::drawLines(const std::vector<SDL_Point> points) const
{
	if(points.empty()) {
		return false;
	}
	return SDL_RenderDrawLines(renderer_.get(), points.data(),
		points.size()) >= 0;
}

bool Renderer::drawRect(const SDL_Rect *rect) const
{
	return SDL_RenderDrawRect(renderer_.get(), rect) >= 0;
}

bool Renderer::drawRects(const std::vector<SDL_Rect> rects) const
{
	if(rects.empty()) {
		return false;
	}
	return SDL_RenderDrawRects(renderer_.get(), rects.data(),
		rects.size()) >= 0;
}

bool Renderer::fillRect(const SDL_Rect *rect) const
{
	return SDL_RenderFillRect(renderer_.get(), rect);
}

bool Renderer::fillRects(const std::vector<SDL_Rect> rects) const
{
	if(rects.empty()) {
		return false;
	}
	return SDL_RenderFillRects(renderer_.get(), rects.data(),
		rects.size()) >= 0;
}