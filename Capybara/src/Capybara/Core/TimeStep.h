#pragma once
namespace Capybara
{
    class TimeStep
    {
    public:
        TimeStep() {}
        TimeStep(float time)
            : m_Time(time)
        {
        }
        operator float() const { return m_Time; }
        operator float() { return m_Time; }
        inline float GetSeconds() const { return m_Time; }
        inline float GetMilliseconds() const { return m_Time * 1000.0f; }
    private:
        float m_Time = 0.0f;
    };

}
