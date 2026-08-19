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

    void *SDLRendererAPI::GetNativeRenderer()
    {
        return m_Renderer;
    }
}