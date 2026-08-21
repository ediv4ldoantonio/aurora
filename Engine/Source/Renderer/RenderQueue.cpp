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
}