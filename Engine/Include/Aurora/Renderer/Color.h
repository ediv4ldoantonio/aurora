#pragma once

#include <cstdint>

namespace Aurora
{

    struct Color
    {
        uint8_t R = 255;
        uint8_t G = 255;
        uint8_t B = 255;
        uint8_t A = 255;

        constexpr Color() = default;

        constexpr Color(
            uint8_t r,
            uint8_t g,
            uint8_t b,
            uint8_t a = 255)
            : R(r),
              G(g),
              B(b),
              A(a)
        {
        }

        constexpr bool operator==(
            const Color &other) const
        {
            return R == other.R &&
                   G == other.G &&
                   B == other.B &&
                   A == other.A;
        }

        constexpr bool operator!=(
            const Color &other) const
        {
            return !(*this == other);
        }

        static const Color White;
        static const Color Black;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Yellow;
        static const Color Cyan;
        static const Color Magenta;
    };

}