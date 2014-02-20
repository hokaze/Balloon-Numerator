#ifndef PPM__TIMER
#define PPM__TIMER

#include "common.h"

namespace PPM
{
    class Timer
    {
        private:
            int startTicks, pausedTicks;
            bool started, paused;
        public:
            Timer();
            ~Timer();
            void start();
            void stop();
            void pause();
            void unpause();
            int restart();
            int ticks();
            bool getStarted();
            bool getPaused();
    };
}

#endif