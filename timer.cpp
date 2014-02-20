#include "timer.h"

namespace PPM
{
    Timer::Timer()
    {
        startTicks = 0;
        pausedTicks = 0;
        started = false;
        paused = false;
    }
    
    Timer::~Timer()
    {
    }
    
    void Timer::start()
    {
        started = true;
        paused  = false;
        startTicks = SDL_GetTicks();
    }
    
    void Timer::stop()
    {
        started = false;
        paused = false;
    }
    
    void Timer::pause()
    {
        if (started && !paused)
        {
            paused = true;
            pausedTicks = SDL_GetTicks() - startTicks;
        }
    }
    
    void Timer::unpause()
    {
        if (paused)
        {
            paused = false;
            startTicks = SDL_GetTicks() - pausedTicks;
            pausedTicks = 0;
        }
    }
    
    int Timer::restart()
    {
        int elapsedTicks = ticks();
        start();
        return elapsedTicks;
    }

    int Timer::ticks()
    {
        if (started)
        {
            if (paused)
            {
                return pausedTicks;
            }
            else
            {
                return SDL_GetTicks() - startTicks;
            }
        }
        return 0;
    }
    
    bool Timer::getStarted()
    {
        return started;
    }
    
    bool Timer::getPaused()
    {
        return paused;
    }
}