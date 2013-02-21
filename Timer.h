#pragma once

namespace Aggrotech
{
    class Timer
    {
    public:

        Timer();

        void Tick();
        float GetDeltaSinceLastTick();

    private:

        double secondsPerCount;
        __int64 prevCount;
        float delta;
    };
}
