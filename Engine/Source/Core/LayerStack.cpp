#include "Aurora/Core/LayerStack.h"

namespace Aurora
{

    LayerStack::~LayerStack()
    {
        Clear();
    }

    void LayerStack::PushLayer(std::unique_ptr<Layer> layer)
    {
        m_Layers.emplace(
            m_Layers.begin() + m_LayerInsertIndex,
            std::move(layer));

        ++m_LayerInsertIndex;

        layer->OnAttach();
    }

    void LayerStack::PushOverlay(std::unique_ptr<Layer> overlay)
    {
        m_Layers.emplace_back(std::move(overlay));

        overlay->OnAttach();
    }

    void LayerStack::OnEvent(
        Event &event)
    {

        for (auto it = m_Layers.rbegin();
             it != m_Layers.rend();
             ++it)
        {

            (*it)->OnEvent(event);

            if (event.Handled)
                break;
        }
    }

    void LayerStack::Clear()
    {
        for (auto it = m_Layers.rbegin();
             it != m_Layers.rend();
             ++it)
        {
            (*it)->OnDetach();
        }
    }
}