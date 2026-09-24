#pragma once

#include <cstdint>

namespace Aurora
{
    using KeyCode = uint16_t;

    namespace Key
    {
        // Unknown
        constexpr KeyCode Unknown = 0;

        // Letters
        constexpr KeyCode A = 'A';
        constexpr KeyCode B = 'B';
        constexpr KeyCode C = 'C';
        constexpr KeyCode D = 'D';
        constexpr KeyCode E = 'E';
        constexpr KeyCode F = 'F';
        constexpr KeyCode G = 'G';
        constexpr KeyCode H = 'H';
        constexpr KeyCode I = 'I';
        constexpr KeyCode J = 'J';
        constexpr KeyCode K = 'K';
        constexpr KeyCode L = 'L';
        constexpr KeyCode M = 'M';
        constexpr KeyCode N = 'N';
        constexpr KeyCode O = 'O';
        constexpr KeyCode P = 'P';
        constexpr KeyCode Q = 'Q';
        constexpr KeyCode R = 'R';
        constexpr KeyCode S = 'S';
        constexpr KeyCode T = 'T';
        constexpr KeyCode U = 'U';
        constexpr KeyCode V = 'V';
        constexpr KeyCode W = 'W';
        constexpr KeyCode X = 'X';
        constexpr KeyCode Y = 'Y';
        constexpr KeyCode Z = 'Z';

        // Numbers
        constexpr KeyCode Num0 = '0';
        constexpr KeyCode Num1 = '1';
        constexpr KeyCode Num2 = '2';
        constexpr KeyCode Num3 = '3';
        constexpr KeyCode Num4 = '4';
        constexpr KeyCode Num5 = '5';
        constexpr KeyCode Num6 = '6';
        constexpr KeyCode Num7 = '7';
        constexpr KeyCode Num8 = '8';
        constexpr KeyCode Num9 = '9';

        // Function keys
        constexpr KeyCode F1 = 256;
        constexpr KeyCode F2 = 257;
        constexpr KeyCode F3 = 258;
        constexpr KeyCode F4 = 259;
        constexpr KeyCode F5 = 260;
        constexpr KeyCode F6 = 261;
        constexpr KeyCode F7 = 262;
        constexpr KeyCode F8 = 263;
        constexpr KeyCode F9 = 264;
        constexpr KeyCode F10 = 265;
        constexpr KeyCode F11 = 266;
        constexpr KeyCode F12 = 267;
        constexpr KeyCode F13 = 268;
        constexpr KeyCode F14 = 269;
        constexpr KeyCode F15 = 270;
        constexpr KeyCode F16 = 271;
        constexpr KeyCode F17 = 272;
        constexpr KeyCode F18 = 273;
        constexpr KeyCode F19 = 274;
        constexpr KeyCode F20 = 275;
        constexpr KeyCode F21 = 276;
        constexpr KeyCode F22 = 277;
        constexpr KeyCode F23 = 278;
        constexpr KeyCode F24 = 279;

        // Modifiers
        constexpr KeyCode LeftShift = 300;
        constexpr KeyCode RightShift = 301;
        constexpr KeyCode LeftControl = 302;
        constexpr KeyCode RightControl = 303;
        constexpr KeyCode LeftAlt = 304;
        constexpr KeyCode RightAlt = 305;
        constexpr KeyCode LeftSuper = 306;
        constexpr KeyCode RightSuper = 307;

        // Arrows
        constexpr KeyCode Up = 400;
        constexpr KeyCode Down = 401;
        constexpr KeyCode Left = 402;
        constexpr KeyCode Right = 403;

        // Common keys
        constexpr KeyCode Space = 500;
        constexpr KeyCode Enter = 501;
        constexpr KeyCode Escape = 502;
        constexpr KeyCode Backspace = 503;
        constexpr KeyCode Tab = 504;
        constexpr KeyCode CapsLock = 505;

        // Navigation
        constexpr KeyCode Insert = 510;
        constexpr KeyCode Delete = 511;
        constexpr KeyCode Home = 512;
        constexpr KeyCode End = 513;
        constexpr KeyCode PageUp = 514;
        constexpr KeyCode PageDown = 515;

        // Punctuation
        constexpr KeyCode Apostrophe = 600;
        constexpr KeyCode Comma = 601;
        constexpr KeyCode Minus = 602;
        constexpr KeyCode Period = 603;
        constexpr KeyCode Slash = 604;
        constexpr KeyCode Semicolon = 605;
        constexpr KeyCode Equals = 606;
        constexpr KeyCode LeftBracket = 607;
        constexpr KeyCode RightBracket = 608;
        constexpr KeyCode Backslash = 609;
        constexpr KeyCode Grave = 610;

        // Keypad
        constexpr KeyCode KP0 = 700;
        constexpr KeyCode KP1 = 701;
        constexpr KeyCode KP2 = 702;
        constexpr KeyCode KP3 = 703;
        constexpr KeyCode KP4 = 704;
        constexpr KeyCode KP5 = 705;
        constexpr KeyCode KP6 = 706;
        constexpr KeyCode KP7 = 707;
        constexpr KeyCode KP8 = 708;
        constexpr KeyCode KP9 = 709;

        constexpr KeyCode KPDecimal = 710;
        constexpr KeyCode KPDivide = 711;
        constexpr KeyCode KPMultiply = 712;
        constexpr KeyCode KPMinus = 713;
        constexpr KeyCode KPPlus = 714;
        constexpr KeyCode KPEnter = 715;

        // Lock / system
        constexpr KeyCode PrintScreen = 800;
        constexpr KeyCode ScrollLock = 801;
        constexpr KeyCode Pause = 802;
        constexpr KeyCode NumLock = 803;
        constexpr KeyCode Menu = 804;
    }
}