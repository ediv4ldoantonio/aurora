#include <Aurora/Core/Time.h>
#include <chrono>

namespace Aurora
{

    namespace
    {
        using Clock = std::chrono::high_resolution_clock;

        Clock::time_point s_Start = Clock::now();
        Clock::time_point s_Last = s_Start;

        float s_Delta = 0.0f;
        float s_FPS = 0.0f;
        uint64_t s_Frames = 0;
    }

    void Time::Init()
    {
        s_Start = s_Last = Clock::now();
        s_Delta = 0.0f;
        s_FPS = 0.0f;
        s_Frames = 0;
    }

    float Time::DeltaTime()
    {
        return s_Delta;
    }

    void Time::Update()
    {
        const auto now = Clock::now();

        s_Delta = std::chrono::duration<float>(now - s_Last).count();

        s_Last = now;

        ++s_Frames;

        if (s_Delta > 0.0f)
        {
            const float instant = 1.0f / s_Delta;
            s_FPS = (s_FPS == 0.0f) ? instant : s_FPS + (instant - s_FPS) * 0.05f; // exponential smoothing
        }
    }

    double Time::GetElapsedTime()
    {
        return std::chrono::duration<double>(Clock::now() - s_Start).count();
    }

    uint64_t Time::GetFrameCount()
    {
        return s_Frames;
    }

    float Time::GetFPS()
    {
        return s_FPS;
    }
}