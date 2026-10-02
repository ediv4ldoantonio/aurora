#include "Aurora/Math/Vector2.h"
#include "Aurora/Core/Logger.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>

using namespace Aurora;

// ------------------------------------------------------------------------------------------
// Mini harness
// ------------------------------------------------------------------------------------------
static int g_Checks = 0;
static int g_Failures = 0;

#define CHECK(...)                                                                        \
    do                                                                                    \
    {                                                                                     \
        ++g_Checks;                                                                       \
        if (!(__VA_ARGS__))                                                               \
        {                                                                                 \
            ++g_Failures;                                                                 \
            std::fprintf(stderr, "  FAIL %s:%d  %s\n", __FILE__, __LINE__, #__VA_ARGS__); \
        }                                                                                 \
    } while (false)

#define CHECK_NEAR(a, b) CHECK(std::abs(static_cast<float>(a) - static_cast<float>(b)) < 1e-3f)
#define CHECK_VEC(v, ex, ey) CHECK(std::abs((v).x - (ex)) < 1e-3f && std::abs((v).y - (ey)) < 1e-3f)

#define RUN(test)                                                                \
    do                                                                           \
    {                                                                            \
        const int before = g_Failures;                                           \
        test();                                                                  \
        std::printf("[%s] %s\n", g_Failures == before ? " OK " : "FAIL", #test); \
    } while (false)

// ------------------------------------------------------------------------------------------
// Math
// ------------------------------------------------------------------------------------------
static void Test_Vector2()
{
    const Vector2 a{3.0f, 4.0f};
    CHECK_NEAR(a.Length(), 5.0f);
    CHECK_VEC(a.Normalized(), 0.6f, 0.8f);
    CHECK_VEC(Vector2::Zero().Normalized(), 0.0f, 0.0f);
    CHECK_VEC(a + Vector2(1, 1), 4.0f, 5.0f);
    CHECK_VEC(a * 2.0f, 6.0f, 8.0f);
    CHECK_VEC(a * Vector2(2, 0.5f), 6.0f, 2.0f);
    CHECK_NEAR(a.Dot(Vector2(1, 0)), 3.0f);

    // +Y is down, so a positive 90 degree rotation maps +X onto +Y.
    CHECK_VEC(Vector2(1, 0).Rotated(Math::ToRadians(90.0f)), 0.0f, 1.0f);
}

int main()
{
    Logger::SetLevel(LogLevel::Warn);

    RUN(Test_Vector2);

    std::printf("\n%d checks, %d failure(s)\n", g_Checks, g_Failures);
    return g_Failures == 0 ? 0 : 1;
}
