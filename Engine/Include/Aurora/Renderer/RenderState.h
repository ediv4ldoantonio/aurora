#pragma once

#include "Aurora/Math/Matrix4.h"

namespace Aurora
{

    struct RenderState
    {
        Matrix4 ViewMatrix =
            Matrix4::Identity();

        Matrix4 ProjectionMatrix =
            Matrix4::Identity();
    };

}