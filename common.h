// Includes to be used everywhere
#ifndef PPM__COMMON
#define PPM__COMMON

// Visual Studio needs slightly different include statements
#ifdef _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
	//#include "SDL_ttf.h"
    //#include "SDL_mixer.h"
#endif
// Normal SDL includes for other platforms/compilers
#ifndef _WIN32
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_image.h"
	//#include "SDL2/SDL_ttf.h"
    //#include "SDL2/SDL_mixer.h"
#endif

#include <string>
#include <vector>
#include <iostream> // DEBUG
#include <stdlib.h> // needed for srand, rand
#include <time.h>

#endif