#include "Aurora/Renderer/RenderQueue.h"

#include <algorithm>

namespace Aurora
{

    void RenderQueue::Submit(
        const SpriteDrawCommand &command)
    {
        SpriteDrawCommand submitted =
            command;

        submitted.SortKey.SubmissionOrder =
            m_SubmissionCounter++;

        m_Commands.push_back(
            submitted);
    }

    void RenderQueue::Clear()
    {
        m_Commands.clear();

        m_SubmissionCounter = 0;
    }

    const std::vector<SpriteDrawCommand> &
    RenderQueue::GetCommands() const
    {
        return m_Commands;
    }

    bool RenderQueue::Empty() const
    {
        return m_Commands.empty();
    }

    size_t RenderQueue::Size() const
    {
        return m_Commands.size();
    }

    void RenderQueue::Sort()
    {
        std::stable_sort(
            m_Commands.begin(),
            m_Commands.end(),
            [](const SpriteDrawCommand &a,
               const SpriteDrawCommand &b)
            {
                return a.SortKey <
                       b.SortKey;
            });
    }

    bool RenderQueue::IsSorted() const
    {
        return std::is_sorted(
            m_Commands.begin(),
            m_Commands.end(),
            [](const SpriteDrawCommand &a,
               const SpriteDrawCommand &b)
            {
                return a.SortKey <
                       b.SortKey;
            });
    }

    void RenderQueue::OptimizeForBatching()
    {
        if (m_Commands.size() < 2)
            return;

        size_t start = 0;

        while (start < m_Commands.size())
        {
            const RenderPass pass =
                m_Commands[start]
                    .SortKey.Pass;

            const int32_t layer =
                m_Commands[start]
                    .SortKey.Layer;

            size_t end = start + 1;

            while (end < m_Commands.size())
            {
                const auto &command =
                    m_Commands[end];

                if (command.SortKey.Pass != pass)
                    break;

                if (command.SortKey.Layer != layer)
                    break;

                ++end;
            }

            size_t runStart = start;

            while (runStart < end)
            {
                if (!m_Commands[runStart]
                         .CanReorderForBatching())
                {
                    ++runStart;
                    continue;
                }

                size_t runEnd =
                    runStart + 1;

                while (runEnd < end &&
                       m_Commands[runEnd]
                           .CanReorderForBatching())
                {
                    ++runEnd;
                }

                std::stable_sort(
                    m_Commands.begin() + runStart,
                    m_Commands.begin() + runEnd,
                    [](const SpriteDrawCommand &a,
                       const SpriteDrawCommand &b)
                    {
                        return a.Batch <
                               b.Batch;
                    });

                runStart = runEnd;
            }

            start = end;
        }
    }
}