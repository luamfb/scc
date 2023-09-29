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

#ifndef SCC_WINDOW_HPP
#define SCC_WINDOW_HPP

#include <memory>
#include <SDL.h>
#include "renderer.hpp"

namespace SDL {

class Window {
	// TODO: hide window, fullscreen, close window...
public:
	static const int DEFAULT_WIDTH = 800;
	static const int DEFAULT_HEIGHT = 600;
	static const int DEFAULT_X_COORD = SDL_WINDOWPOS_UNDEFINED;
	static const int DEFAULT_Y_COORD = SDL_WINDOWPOS_UNDEFINED;
	static const Uint32 DEFAULT_INIT_FLAGS = 0;

	// Having Renderer as Window's member object is the easiest way of
	// ensuring that every Window has 1 and only 1 renderer, and that the
	// Renderer doesn't outlive its Window.
	// The downside is that users can't render the old way
	// (ie, blitting directly to the Window's surface).
	Renderer renderer;

	Window(const char *title,
		int width = DEFAULT_WIDTH,
		int height = DEFAULT_HEIGHT,
		int x = DEFAULT_X_COORD,
		int y = DEFAULT_Y_COORD,
		Uint32 flags = DEFAULT_INIT_FLAGS,
		Uint32 rendererFlags = Renderer::DEFAULT_INIT_FLAGS);

	// I don't think SDL has any way of copying windows...
	Window(const Window &that) = delete;
	Window(Window &&that) = default;
	~Window() = default;
	Window & operator=(Window that);
	friend void swap(Window &first, Window &second) noexcept;

	// SDL_GetWindowSize(). You may pass NULL as a parameter if you're not
	// interested in its value, though you can also use getWidth() or
	// getHeight() in that case
	void getSize(int *width, int *height) const;

	// wrappers around SDL_GetWindowSize(), but they return the value.
	int getWidth() const;
	int getHeight() const;

	struct Deleter {
		void operator()(SDL_Window *window)
		{
			SDL_DestroyWindow(window);
		}
	};
private:
	std::unique_ptr<SDL_Window, Deleter> window_;
};

} // namespace SDL

#endif
