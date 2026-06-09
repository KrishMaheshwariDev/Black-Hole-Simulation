#pragma once

#include <GLFW/glfw3.h>
#include <algorithm>

class FixedTimestep{
    public:
        explicit FixedTimestep(float ticksPerSeconds);

        void update();

        bool HasPendingTick() const;

        void ConsumeTick();

        float GetFixedDeltaTime() const;

    private:
        float m_TicksPerSecond;
        float m_FixedDeltaTime;

        float m_Accumulator;
        float m_LastTime;
};