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

#ifndef SCC_GLOBJECT_HPP
#define SCC_GLOBJECT_HPP

#include "GL/common.hpp"

namespace GL {

// again, in the openGL sense of the word
class Object {
public:
	virtual void bind(GLenum target) = 0;
	virtual void unbind(GLenum target) = 0;
	virtual ~Object() {}
};

} // namespace GL

#endif // SCC_GLOBJECT_HPP