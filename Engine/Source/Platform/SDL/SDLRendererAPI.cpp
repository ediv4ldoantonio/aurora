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

        verts[0].color.r = command.Tint.R;
        verts[0].color.g = command.Tint.G;
        verts[0].color.b = command.Tint.B;
        verts[0].color.a = command.Tint.A;

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

        if (command.Texture)
        {
            auto *texture =
                static_cast<SDLTexture2D *>(
                    command.Texture);

            SDL_Texture *native =
                texture->GetNativeTexture();

            SDL_SetTextureColorMod(
                native,
                command.Tint.R,
                command.Tint.G,
                command.Tint.B);

            SDL_SetTextureAlphaMod(
                native,
                command.Tint.A);

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

        if (vertices.empty())
            return;

        SDL_Vertex *
            sdlVertices =
                new SDL_Vertex[vertices.size()];

        for (size_t i = 0;
             i < vertices.size();
             ++i)
        {
            sdlVertices[i].position.x =
                vertices[i].Position.x;

            sdlVertices[i].position.y =
                vertices[i].Position.y;

            sdlVertices[i].tex_coord.x =
                vertices[i].TexCoord.x;

            sdlVertices[i].tex_coord.y =
                vertices[i].TexCoord.y;

            sdlVertices[i].color.r =
                vertices[i].Color.R;

            sdlVertices[i].color.g =
                vertices[i].Color.G;

            sdlVertices[i].color.b =
                vertices[i].Color.B;

            sdlVertices[i].color.a =
                vertices[i].Color.A;
        }

        SDL_RenderGeometry(
            m_Renderer,
            nullptr,
            sdlVertices,
            static_cast<int>(
                vertices.size()),
            reinterpret_cast<const int *>(
                indices.data()),
            static_cast<int>(
                indices.size()));

        delete[] sdlVertices;
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
}