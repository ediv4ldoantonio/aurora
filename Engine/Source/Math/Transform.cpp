#include "Aurora/Math/Transform.h"

namespace Aurora
{
    Transform::Transform(
        const Vector2 &position,
        float rotation,
        const Vector2 &scale)
        : Position(position),
          Rotation(rotation),
          Scale(scale)
    {
    }

    Matrix4 Transform::ToMatrix() const
    {
        Matrix4 translation =
            Matrix4::Translation(Position);

        Matrix4 rotation =
            Matrix4::Rotation(Rotation);

        Matrix4 scale =
            Matrix4::Scale(Scale);

        return translation *
               rotation *
               scale;
    }
}