// Includes to be used everywhere
#ifndef PPM__COMMON
#define PPM__COMMON

// Visual Studio needs slightly different include statements
#ifdef _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
#endif
// Normal SDL includes for other platforms/compilers
#ifndef _WIN32
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_image.h"
#endif
#include <string>

#endif