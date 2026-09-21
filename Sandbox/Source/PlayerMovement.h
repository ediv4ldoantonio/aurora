#pragma once

#include "Aurora/Scene/Components/ScriptComponent.h"
#include "Aurora/Input/Input.h"
#include "Aurora/Core/Logger.h"
#include "Aurora/Scene/Components/TransformComponent.h"

class PlayerMovement : public Aurora::ScriptableEntity
{

public:
    void OnUpdate(float dt) override
    {
        auto &transform =
            GetEntity()
                .GetComponent<Aurora::TransformComponent>();

        const float speed = 10.0f;

        if (
            Aurora::Input::IsKeyDown(
                Aurora::Key::D))
        {
            transform.LocalTransform.Position.x +=
                speed * dt;
        }

        if (
            Aurora::Input::IsKeyDown(
                Aurora::Key::A))
        {
            transform.LocalTransform.Position.x +=
                -speed * dt;
        }

        if (
            Aurora::Input::IsKeyDown(
                Aurora::Key::W))
        {
            transform.LocalTransform.Position.y +=
                speed * dt;
        }

        if (
            Aurora::Input::IsKeyDown(
                Aurora::Key::S))
        {
            transform.LocalTransform.Position.y +=
                -speed * dt;
        }

        if (Aurora::Input::IsKeyDown(
                Aurora::Key::E))
        {
            transform.LocalTransform.Rotation += speed * dt;
        }

        if (Aurora::Input::IsKeyDown(
                Aurora::Key::Q))
        {
            transform.LocalTransform.Rotation -= speed * dt;
        }
    }
};