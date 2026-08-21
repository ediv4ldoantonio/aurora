#pragma once

#include "Aurora/Renderer/SpriteDrawCommand.h"

#include <cstdint>
#include <vector>

namespace Aurora
{
    class RenderQueue
    {
    public:
        void Submit(
            const SpriteDrawCommand &command);

        void Clear();

        void Sort();

        const std::vector<SpriteDrawCommand> &
        GetCommands() const;

        bool Empty() const;

        size_t Size() const;

        bool IsSorted() const;

    private:
        std::vector<SpriteDrawCommand>
            m_Commands;

        uint64_t m_SubmissionCounter = 0;
    };
}