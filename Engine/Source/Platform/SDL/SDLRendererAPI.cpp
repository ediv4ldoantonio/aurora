#include "SDLRendererAPI.h"
#include "SDLTexture2D.h"
#include "Aurora/Core/Logger.h"

#include <SDL3/SDL.h>

#include <cmath>

namespace Aurora
{

    SDLRendererAPI::SDLRendererAPI(
        SDL_Renderer *renderer)
        : m_Renderer(renderer)
    {
    }

    void SDLRendererAPI::Init()
    {
    }

    void SDLRendererAPI::BeginFrame()
    {
        SDL_SetRenderDrawColor(
            m_Renderer,
            20,
            20,
            20,
            255);

        SDL_RenderClear(
            m_Renderer);
    }

    void SDLRendererAPI::EndFrame()
    {
        SDL_RenderPresent(
            m_Renderer);
    }

    void SDLRendererAPI::DrawSprite(
        const SpriteDrawCommand &command)
    {
        SDL_FRect rect;

        rect.x = command.Position.x;
        rect.y = command.Position.y;

        rect.w = command.Size.x;
        rect.h = command.Size.y;

        float x = rect.x;
        float y = rect.y;

        float w = rect.w;
        float h = rect.h;

        float cx = x + w * 0.5f;
        float cy = y + h * 0.5f;

        float angleDeg =
            command.Rotation;

        float angle =
            angleDeg *
            (3.14159265358979323846f / 180.0f);

        float c = std::cos(angle);
        float s = std::sin(angle);

        float hx = w * 0.5f;
        float hy = h * 0.5f;

        SDL_Vertex verts[4];

        verts[0].position.x =
            cx + (-hx) * c - (-hy) * s;

        verts[0].position.y =
            cy + (-hx) * s + (-hy) * c;

        verts[0].tex_coord.x = 0.0f;
        verts[0].tex_coord.y = 0.0f;

        verts[0].color.r = command.MaterialInstance->GetTint().R;
        verts[0].color.g = command.MaterialInstance->GetTint().G;
        verts[0].color.b = command.MaterialInstance->GetTint().B;
        verts[0].color.a = command.MaterialInstance->GetTint().A;

        // Top-right
        verts[1].position.x =
            cx + hx * c - (-hy) * s;

        verts[1].position.y =
            cy + hx * s + (-hy) * c;

        verts[1].tex_coord.x = 1.0f;
        verts[1].tex_coord.y = 0.0f;
        verts[1].color = verts[0].color;

        // Bottom-right
        verts[2].position.x =
            cx + hx * c - hy * s;

        verts[2].position.y =
            cy + hx * s + hy * c;

        verts[2].tex_coord.x = 1.0f;
        verts[2].tex_coord.y = 1.0f;
        verts[2].color = verts[0].color;

        // Bottom-left
        verts[3].position.x =
            cx + (-hx) * c - hy * s;

        verts[3].position.y =
            cy + (-hx) * s + hy * c;

        verts[3].tex_coord.x = 0.0f;
        verts[3].tex_coord.y = 1.0f;
        verts[3].color = verts[0].color;

        int indices[6] =
            {
                0, 1, 2,
                2, 3, 0};

        if (command.MaterialInstance && command.MaterialInstance->GetTexture())
        {
            auto *texture =
                static_cast<SDLTexture2D *>(
                    command.MaterialInstance->GetTexture());

            SDL_Texture *native =
                texture->GetNativeTexture();

            SDL_SetTextureColorMod(
                native,
                command.MaterialInstance->GetTint().R,
                command.MaterialInstance->GetTint().G,
                command.MaterialInstance->GetTint().B);

            SDL_SetTextureAlphaMod(
                native,
                command.MaterialInstance->GetTint().A);

            SDL_RenderGeometry(
                m_Renderer,
                native,
                verts,
                4,
                indices,
                6);
        }
        else
        {
            SDL_RenderGeometry(
                m_Renderer,
                nullptr,
                verts,
                4,
                indices,
                6);
        }
    }

    void SDLRendererAPI::DrawSpriteBatch(
        const SpriteBatch &batch)
    {
        const auto &vertices =
            batch.GetVertices();

        const auto &indices =
            batch.GetIndices();

        const auto &textures =
            batch.GetTextures();

        if (vertices.empty())
            return;

        const size_t quadCount =
            vertices.size() / 4;

        for (size_t quad = 0;
             quad < quadCount;
             ++quad)
        {
            const size_t vertexStart =
                quad * 4;

            const size_t indexStart =
                quad * 6;

            const float textureIndex =
                vertices[vertexStart]
                    .TextureIndex;

            SDL_Texture *texture =
                nullptr;

            if (textureIndex > 0.0f)
            {
                const size_t textureSlot =
                    static_cast<size_t>(
                        textureIndex) -
                    1;

                if (textureSlot <
                    textures.size())
                {
                    auto *texture2D =
                        textures[textureSlot];

                    if (texture2D)
                    {
                        auto *sdlTexture =
                            static_cast<
                                SDLTexture2D *>(
                                texture2D);

                        texture =
                            sdlTexture->GetNativeTexture();
                    }
                }
            }

            SDL_Vertex quadVertices[4];

            for (int i = 0; i < 4; ++i)
            {
                quadVertices[i] =
                    ToSDLVertex(
                        vertices[vertexStart + i]);
            }

            int quadIndices[6];

            for (int i = 0; i < 6; ++i)
            {
                quadIndices[i] =
                    static_cast<int>(
                        indices[indexStart + i] -
                        static_cast<uint32_t>(
                            vertexStart));
            }

            SDL_RenderGeometry(
                m_Renderer,
                texture,
                quadVertices,
                4,
                quadIndices,
                6);
        }
    }

    void SDLRendererAPI::Clear()
    {
        SDL_RenderClear(m_Renderer);
    }

    void *SDLRendererAPI::GetNativeRenderer()
    {
        return m_Renderer;
    }

    void SDLRendererAPI::SetViewport(
        int x,
        int y,
        int width,
        int height)
    {
        SDL_Rect viewport;

        viewport.x = x;
        viewport.y = y;
        viewport.w = width;
        viewport.h = height;

        SDL_SetRenderViewport(
            m_Renderer,
            &viewport);
    }

    SDL_Vertex SDLRendererAPI::ToSDLVertex(
        const SpriteVertex &vertex)
    {
        SDL_Vertex result;

        result.position.x =
            vertex.Position.x;

        result.position.y =
            vertex.Position.y;

        result.tex_coord.x =
            vertex.TexCoord.x;

        result.tex_coord.y =
            vertex.TexCoord.y;

        result.color.r =
            vertex.Color.R;

        result.color.g =
            vertex.Color.G;

        result.color.b =
            vertex.Color.B;

        result.color.a =
            vertex.Color.A;

        return result;
    }
}