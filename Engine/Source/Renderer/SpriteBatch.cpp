#include "Aurora/Renderer/SpriteBatch.h"

#include <cmath>

namespace Aurora
{

    void SpriteBatch::Clear()
    {
        m_Vertices.clear();
        m_Indices.clear();
        m_Materials.clear();

        m_HasBatchKey = false;
        m_BatchKey = {};
    }

    bool SpriteBatch::CanBatchWith(
        const BatchKey &key) const
    {
        if (!m_HasBatchKey)
            return true;

        return m_BatchKey == key;
    }

    const std::vector<SpriteVertex> &
    SpriteBatch::GetVertices() const
    {
        return m_Vertices;
    }

    const std::vector<uint32_t> &
    SpriteBatch::GetIndices() const
    {
        return m_Indices;
    }

    uint32_t SpriteBatch::GetMaterialSlot(
        Material *material)
    {
        if (!material)
            return 0;

        for (uint32_t i = 0;
             i < m_Materials.size();
             ++i)
        {
            if (m_Materials[i] == material)
                return i + 1;
        }

        m_Materials.push_back(material);

        return static_cast<uint32_t>(
            m_Materials.size());
    }

    void SpriteBatch::AddQuad(
        const Vector2 &position,
        const Vector2 &size,
        float rotation,
        Material *material,
        const BatchKey &batchKey)
    {
        if (!m_HasBatchKey)
        {
            m_BatchKey = batchKey;
            m_HasBatchKey = true;
        }

        const uint32_t baseIndex =
            static_cast<uint32_t>(
                m_Vertices.size());

        const uint32_t materialSlot =
            GetMaterialSlot(material);

        const float materialIndex =
            static_cast<float>(
                materialSlot);

        Color color =
            Color::White;

        if (material)
            color = material->GetTint();

        const float halfWidth =
            size.x * 0.5f;

        const float halfHeight =
            size.y * 0.5f;

        const float radians =
            rotation *
            (3.14159265358979323846f / 180.0f);

        const float cosine =
            std::cos(radians);

        const float sine =
            std::sin(radians);

        auto rotatePoint =
            [&](float x, float y)
        {
            Vector2 result;

            result.x =
                position.x +
                x * cosine -
                y * sine;

            result.y =
                position.y +
                x * sine +
                y * cosine;

            return result;
        };

        SpriteVertex vertices[4];

        vertices[0].Position =
            rotatePoint(
                -halfWidth,
                -halfHeight);

        vertices[1].Position =
            rotatePoint(
                halfWidth,
                -halfHeight);

        vertices[2].Position =
            rotatePoint(
                halfWidth,
                halfHeight);

        vertices[3].Position =
            rotatePoint(
                -halfWidth,
                halfHeight);

        vertices[0].TexCoord = {0.0f, 0.0f};
        vertices[1].TexCoord = {1.0f, 0.0f};
        vertices[2].TexCoord = {1.0f, 1.0f};
        vertices[3].TexCoord = {0.0f, 1.0f};

        for (auto &vertex : vertices)
        {
            vertex.Color = color;
            vertex.MaterialIndex = materialIndex;
        }

        for (const auto &vertex : vertices)
            m_Vertices.push_back(vertex);

        m_Indices.push_back(baseIndex + 0);
        m_Indices.push_back(baseIndex + 1);
        m_Indices.push_back(baseIndex + 2);

        m_Indices.push_back(baseIndex + 2);
        m_Indices.push_back(baseIndex + 3);
        m_Indices.push_back(baseIndex + 0);
    }

    bool SpriteBatch::CanAdd(
        Material *material) const
    {
        if (m_Vertices.size() + 4 >
            MaxVertices)
        {
            return false;
        }

        if (m_Indices.size() + 6 >
            MaxIndices)
        {
            return false;
        }

        if (!material)
            return true;

        for (const auto &existing :
             m_Materials)
        {
            if (existing == material)
                return true;
        }

        return m_Materials.size() <
               MaxMaterialSlots - 1;
    }

    bool SpriteBatch::IsFull() const
    {
        return m_Vertices.size() + 4 >
                   MaxVertices ||
               m_Indices.size() + 6 >
                   MaxIndices ||
               m_Materials.size() >=
                   MaxMaterialSlots;
    }

    const std::vector<Material *> &
    SpriteBatch::GetMaterials() const
    {
        return m_Materials;
    }

    const BatchKey &
    SpriteBatch::GetBatchKey() const
    {
        return m_BatchKey;
    }
}