#pragma once

#include "Aurora/Renderer/SpriteVertex.h"
#include "Aurora/Renderer/Texture2D.h"

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
            const Color &color,
            Texture2D *texture);

        const std::vector<SpriteVertex> &
        GetVertices() const;

        const std::vector<uint32_t> &
        GetIndices() const;

        const std::vector<Texture2D *> &
        GetTextures() const;

    private:
        uint32_t GetTextureSlot(
            Texture2D *texture);

        std::vector<SpriteVertex>
            m_Vertices;

        std::vector<uint32_t>
            m_Indices;

        std::vector<Texture2D *>
            m_Textures;
    };

}