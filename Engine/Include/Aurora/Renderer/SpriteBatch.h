#pragma once

#include "Aurora/Renderer/SpriteVertex.h"
#include "Aurora/Renderer/Material.h"
#include "Aurora/Renderer/BatchKey.h"

#include <vector>

namespace Aurora
{
    class SpriteBatch
    {
    public:
        static constexpr uint32_t MaxQuads = 1000;

        static constexpr uint32_t MaxVertices =
            MaxQuads * 4;

        static constexpr uint32_t MaxIndices =
            MaxQuads * 6;

        static constexpr uint32_t MaxMaterialSlots = 16;

    public:
        void Clear();

        bool CanAdd(
            Material *material) const;

        bool CanBatchWith(
            const BatchKey &key) const;

        bool IsFull() const;

        void AddQuad(
            const Vector2 &position,
            const Vector2 &size,
            float rotation,
            Material *material,
            const BatchKey &batchKey);

        const std::vector<SpriteVertex> &
        GetVertices() const;

        const std::vector<uint32_t> &
        GetIndices() const;

        const std::vector<Material *> &
        GetMaterials() const;

        const BatchKey &
        GetBatchKey() const;

        size_t GetVertexCount() const;
        size_t GetIndexCount() const;

    private:
        uint32_t GetMaterialSlot(
            Material *material);

    private:
        std::vector<SpriteVertex>
            m_Vertices;

        std::vector<uint32_t>
            m_Indices;

        std::vector<Material *>
            m_Materials;

        bool m_HasBatchKey = false;
        BatchKey m_BatchKey;
    };
}