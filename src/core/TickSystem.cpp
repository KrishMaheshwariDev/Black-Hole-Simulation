#include "TickSystem.hpp"

FixedTimestep::FixedTimestep(float ticksPerSecond)
    : m_TicksPerSecond(ticksPerSecond),
      m_FixedDeltaTime(1.0f / ticksPerSecond),
      m_Accumulator(0.0f),
      m_LastTime(static_cast<float>(glfwGetTime()))
{
}

void FixedTimestep::update()
{
    float currentTime = static_cast<float>(glfwGetTime());

    float frameTime = currentTime - m_LastTime;
    frameTime = std::min(frameTime, 0.25f);
    m_LastTime = currentTime;

    m_Accumulator += frameTime;
}

bool FixedTimestep::HasPendingTick() const
{
    return m_Accumulator >= m_FixedDeltaTime;
}

void FixedTimestep::ConsumeTick()
{
    m_Accumulator -= m_FixedDeltaTime;
}

float FixedTimestep::GetFixedDeltaTime() const
{
    return m_FixedDeltaTime;
}