#pragma once

#include "Aurora/Scene/Components/Component.h"
#include "Aurora/Math/Transform.h"
#include "Aurora/Math/Matrix4.h"

namespace Aurora
{

    struct TransformComponent : public Component
    {
        Aurora::Transform LocalTransform;
        Aurora::Transform WorldTransform;
    };

}