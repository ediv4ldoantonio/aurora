#pragma once

#include "Aurora/Scene/Components/Component.h"
#include "ScriptableEntity.h"

#include <memory>
#include <functional>
#include <tuple>
#include <utility>

namespace Aurora
{
    struct ScriptComponent : public Component
    {
        std::unique_ptr<ScriptableEntity> Instance;

        std::function<
            std::unique_ptr<ScriptableEntity>()>
            InstantiateScript;

        template <typename T, typename... Args>
        void Bind(Args &&...args)
        {
            InstantiateScript =
                [args = std::make_tuple(std::forward<Args>(args)...)]() mutable
            {
                return std::apply(
                    [](auto &&...args)
                    {
                        return std::make_unique<T>(
                            std::forward<decltype(args)>(args)...);
                    },
                    args);
            };
        }
    };

}