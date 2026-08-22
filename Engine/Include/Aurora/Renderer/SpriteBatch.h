#pragma once

#include "Aurora/Renderer/SpriteVertex.h"
#include "Aurora/Renderer/Texture2D.h"

#include <vector>

namespace Aurora
{
    class Material;

    class SpriteBatch
    {

    public:
        static constexpr uint32_t MaxQuads = 1000;

        static constexpr uint32_t MaxVertices =
            MaxQuads * 4;

        static constexpr uint32_t MaxIndices =
            MaxQuads * 6;

        static constexpr uint32_t MaxTextureSlots = 16;

        void Clear();

        void AddQuad(
            const Vector2 &position,
            const Vector2 &size,
            float rotation,
            Material *material);

        bool CanAdd(
            Texture2D *texture) const;

        bool IsFull() const;

        const std::vector<SpriteVertex> &
        GetVertices() const;

        const std::vector<uint32_t> &
        GetIndices() const;

        const std::vector<Texture2D *> &
        GetTextures() const;

        const std::vector<Material *> &
        GetMaterials() const;

    private:
        uint32_t GetTextureSlot(
            Texture2D *texture);

        std::vector<SpriteVertex>
            m_Vertices;

        std::vector<uint32_t>
            m_Indices;

        std::vector<Texture2D *>
            m_Textures;

        std::vector<Material *> m_Materials;
    };

}