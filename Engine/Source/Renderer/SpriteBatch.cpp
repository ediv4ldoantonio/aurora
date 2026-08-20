#include "Aurora/Renderer/SpriteBatch.h"

#include <cmath>

namespace Aurora
{

    void SpriteBatch::Clear()
    {
        m_Vertices.clear();
        m_Indices.clear();
        m_Textures.clear();
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

    uint32_t SpriteBatch::GetTextureSlot(
        Texture2D *texture)
    {
        if (!texture)
            return 0;

        for (uint32_t i = 0;
             i < m_Textures.size();
             ++i)
        {
            if (m_Textures[i] == texture)
                return i;
        }

        m_Textures.push_back(texture);

        return static_cast<uint32_t>(
            m_Textures.size() - 1);
    }

    void SpriteBatch::AddQuad(
        const Vector2 &position,
        const Vector2 &size,
        float rotation,
        const Color &color,
        Texture2D *texture)
    {
        uint32_t textureSlot =
            GetTextureSlot(texture);

        float textureIndex =
            static_cast<float>(textureSlot);

        const uint32_t baseIndex =
            static_cast<uint32_t>(
                m_Vertices.size());

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

        vertices[0].Color = color;
        vertices[1].Color = color;
        vertices[2].Color = color;
        vertices[3].Color = color;

        vertices[0].TextureIndex =
            textureIndex;

        vertices[1].TextureIndex =
            textureIndex;

        vertices[2].TextureIndex =
            textureIndex;

        vertices[3].TextureIndex =
            textureIndex;

        for (const auto &vertex : vertices)
        {
            m_Vertices.push_back(vertex);
        }

        m_Indices.push_back(baseIndex + 0);
        m_Indices.push_back(baseIndex + 1);
        m_Indices.push_back(baseIndex + 2);

        m_Indices.push_back(baseIndex + 2);
        m_Indices.push_back(baseIndex + 3);
        m_Indices.push_back(baseIndex + 0);
    }

    const std::vector<Texture2D *> &
    SpriteBatch::GetTextures() const
    {
        return m_Textures;
    }
}