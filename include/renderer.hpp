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

#ifndef SCC_RENDERER_HPP
#define SCC_RENDERER_HPP

#include <memory>
#include <vector>
#include <SDL.h>
#include "texture.hpp"

namespace SDL {

class Window;
class Surface;

// This class is meant to live only as a Window member object.
class Renderer {
public:
	static const Uint32 DEFAULT_INIT_FLAGS =
		SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC
		| SDL_RENDERER_TARGETTEXTURE;

	Renderer(SDL_Window *window, Uint32 flags);

	// an empty ctor is needed to construct Window. Ugly, but it works.
	Renderer();

	template <typename ... Args>
	Texture makeTexture(Args&& ... args)
	{
		return Texture(renderer_.get(), std::forward<Args>(args)...);
	}

	void present();
	void clear();
	bool setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
	bool getDrawColor(Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a) const;

	// Remember you need to call present() when you're done rendering!

	// renders a part or the entire texture with its own width and height,
	// using SDL_RenderCopy().
	// (x, y): top-left coordinates
	// src: the portion of the texture to be copied, NULL for whole texture
	bool render(Texture &texture, int x, int y,
		const SDL_Rect *src = NULL) const;

	// SDL_RenderCopy()
	bool render(Texture &texture, const SDL_Rect *src = NULL,
		const SDL_Rect *dest = NULL) const;

	// SDL_RenderCopyEx()
	bool render(Texture &texture, const SDL_Rect *src, const SDL_Rect *dest,
		const double angle, const SDL_Point *center,
		const SDL_RendererFlip flip = SDL_FLIP_NONE) const;

	// These will call SDL_SetError if this Renderer wasn't created with
	// SDL_RENDERER_TARGETTEXTURE.
	bool setTarget(Texture &texture);
	// Does the actual work. You can use this to pass either NULL or
	// nullptr, which will set the target as the default
	bool setTarget(SDL_Texture *texture);

	bool setScale(float scaleX, float scaleY);
	void getScale(float *scaleX, float *scaleY) const;

	void getViewport(SDL_Rect *rect) const;
	bool setViewport(const SDL_Rect *rect);

	void getLogicalSize(int *w, int *h) const;
	bool setLogicalSize(int w, int h);

	bool getOutputSize(int *w, int *h) const;
	bool getInfo(SDL_RendererInfo *info) const;

	// "used for drawing operations (Fill and Line)" (SDL wiki)
	bool setDrawBlendMode(SDL_BlendMode mode);
	bool getDrawBlendMode(SDL_BlendMode *mode) const;

	bool drawPoint(int x, int y) const;
	bool drawPoints(const std::vector<SDL_Point> points) const;

	bool drawLine(int x1, int y1, int x2, int y2) const;
	bool drawLine(const SDL_Point &p1, const SDL_Point &p2) const
	{
		return drawLine(p1.x, p1.y, p2.x, p2.y);
	}
	bool drawLines(const std::vector<SDL_Point> points) const;

	bool drawRect(const SDL_Rect *rect) const;
	bool drawRects(const std::vector<SDL_Rect> rects) const;

	bool fillRect(const SDL_Rect *rect) const;
	bool fillRects(const std::vector<SDL_Rect> rects) const;

	// TODO readPixels(), updateTexture(), setClip(), getClip(),
	// isClipEnabled()

	// renderers must NOT be copied. They belong to 1 window only.
	Renderer(const Renderer &that) = delete;
	Renderer(Renderer &&that) = default; // moving is fine though
	~Renderer() = default;
	Renderer & operator=(Renderer that);
	friend void swap(Renderer &first, Renderer &second) noexcept;

	struct Deleter {
		void operator()(SDL_Renderer *renderer)
		{
			SDL_DestroyRenderer(renderer);
		}
	};
private:
	std::unique_ptr<SDL_Renderer, Deleter> renderer_;
};

} // namespace SDL

#endif
