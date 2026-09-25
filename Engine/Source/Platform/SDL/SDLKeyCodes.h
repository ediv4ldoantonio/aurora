#pragma once

#include "Aurora/Input/KeyCodes.h"
#include "Aurora/Events/MouseEvents.h"

#include <SDL3/SDL.h>

namespace Aurora
{

    KeyCode SDLKeyToAurora(
        SDL_Keycode key);

    bool TryGetMouseButton(
        uint8_t button,
        MouseButton &result);

}