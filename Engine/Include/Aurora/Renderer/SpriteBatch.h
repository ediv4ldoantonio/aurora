#pragma once

#include "Aurora/Renderer/SpriteVertex.h"

#include <vector>

namespace Aurora
{

    class SpriteBatch
    {

    public:
        void Clear();

        void AddQuad(
            const Vector2 &position,
            const Vector2 &size,
            float rotation,
            const Color &color);

        const std::vector<SpriteVertex> &
        GetVertices() const;

        const std::vector<uint32_t> &
        GetIndices() const;

    private:
        std::vector<SpriteVertex>
            m_Vertices;

        std::vector<uint32_t>
            m_Indices;
    };

}