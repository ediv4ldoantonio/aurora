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
        m_State = {};
        m_DrawCallCount = 0;

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
        if (!command.MaterialInstance)
            return;

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

        verts[0].color.r = command.MaterialInstance->GetTint().R / 255.0f;
        verts[0].color.g = command.MaterialInstance->GetTint().G / 255.0f;
        verts[0].color.b = command.MaterialInstance->GetTint().B / 255.0f;
        verts[0].color.a = command.MaterialInstance->GetTint().A / 255.0f;

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
            const auto &texture =
                command.MaterialInstance->GetTexture();

            auto *sdlTexture =
                static_cast<SDLTexture2D *>(
                    texture.get());

            SDL_Texture *native =
                sdlTexture->GetNativeTexture();

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

        if (vertices.empty())
            return;

        const auto &materials =
            batch.GetMaterials();

        const size_t quadCount =
            vertices.size() / 4;

        size_t groupStart = 0;

        while (groupStart < quadCount)
        {
            const float materialIndex =
                vertices[groupStart * 4]
                    .MaterialIndex;

            Material *material = nullptr;

            if (materialIndex > 0.0f)
            {
                const size_t slot =
                    static_cast<size_t>(
                        materialIndex) -
                    1;

                if (slot < materials.size())
                {
                    material =
                        materials[slot];
                }
            }

            size_t groupEnd =
                groupStart + 1;

            while (groupEnd < quadCount)
            {
                const float nextMaterialIndex =
                    vertices[groupEnd * 4]
                        .MaterialIndex;

                if (nextMaterialIndex !=
                    materialIndex)
                {
                    break;
                }

                ++groupEnd;
            }

            DrawMaterialRange(
                batch,
                groupStart,
                groupEnd - groupStart,
                material);

            groupStart = groupEnd;
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
            vertex.Color.R / 255.0f;

        result.color.g =
            vertex.Color.G / 255.0f;

        result.color.b =
            vertex.Color.B / 255.0f;

        result.color.a =
            vertex.Color.A / 255.0f;

        return result;
    }

    SDL_BlendMode SDLRendererAPI::ToSDLBlendMode(
        Aurora::BlendMode mode)
    {
        switch (mode)
        {
        case Aurora::BlendMode::Opaque:
            return SDL_BLENDMODE_NONE;

        case Aurora::BlendMode::Alpha:
            return SDL_BLENDMODE_BLEND;

        case Aurora::BlendMode::Additive:
            return SDL_BLENDMODE_ADD;

        case Aurora::BlendMode::Multiply:
            return SDL_BLENDMODE_MOD;
        }

        return SDL_BLENDMODE_NONE;
    }

    void SDLRendererAPI::ApplyTextureMaterial(
        SDL_Texture *texture,
        const Material &material)
    {
        if (!texture)
            return;

        SDL_SetTextureBlendMode(
            texture,
            ToSDLBlendMode(
                material.GetBlendMode()));

        const Color &tint =
            material.GetTint();

        SDL_SetTextureColorMod(
            texture,
            tint.R,
            tint.G,
            tint.B);

        SDL_SetTextureAlphaMod(
            texture,
            tint.A);
    }

    void SDLRendererAPI::ApplyMaterialState(
        Material *material)
    {
        RendererState desired;

        if (material)
        {
            desired.Texture =
                material->GetTexture().get();

            desired.Tint =
                material->GetTint();

            desired.Blend =
                material->GetBlendMode();
        }

        if (desired == m_State)
            return;

        if (desired.Texture)
        {
            auto *texture =
                static_cast<SDLTexture2D *>(
                    desired.Texture);

            SDL_Texture *native =
                texture->GetNativeTexture();

            ApplyTextureMaterial(
                native,
                *material);
        }

        m_State =
            desired;
    }

    void SDLRendererAPI::DrawMaterialRange(
        const SpriteBatch &batch,
        size_t firstQuad,
        size_t quadCount,
        Material *material)
    {
        const auto &vertices =
            batch.GetVertices();

        const auto &indices =
            batch.GetIndices();

        if (quadCount == 0)
            return;

        std::vector<SDL_Vertex> sdlVertices(
            quadCount * 4);

        std::vector<int> sdlIndices(
            quadCount * 6);

        const size_t vertexStart =
            firstQuad * 4;

        const size_t indexStart =
            firstQuad * 6;

        for (size_t i = 0;
             i < quadCount * 4;
             ++i)
        {
            const SpriteVertex &vertex =
                vertices[vertexStart + i];

            SDL_Vertex &output =
                sdlVertices[i];

            output.position.x =
                vertex.Position.x;

            output.position.y =
                vertex.Position.y;

            output.tex_coord.x =
                vertex.TexCoord.x;

            output.tex_coord.y =
                vertex.TexCoord.y;

            output.color.r =
                vertex.Color.R;

            output.color.g =
                vertex.Color.G;

            output.color.b =
                vertex.Color.B;

            output.color.a =
                vertex.Color.A;
        }

        for (size_t i = 0;
             i < quadCount * 6;
             ++i)
        {
            sdlIndices[i] =
                static_cast<int>(
                    indices[indexStart + i] -
                    static_cast<uint32_t>(
                        vertexStart));
        }

        SDL_Texture *nativeTexture =
            nullptr;

        if (material &&
            material->GetTexture())
        {
            auto *texture =
                static_cast<SDLTexture2D *>(
                    material->GetTexture().get());

            nativeTexture =
                texture->GetNativeTexture();
        }

        if (material)
        {
            ApplyMaterialState(material);
        }

        SDL_RenderGeometry(
            m_Renderer,
            nativeTexture,
            sdlVertices.data(),
            static_cast<int>(
                sdlVertices.size()),
            sdlIndices.data(),
            static_cast<int>(
                sdlIndices.size()));

        ++m_DrawCallCount;
    }

    uint32_t SDLRendererAPI::GetDrawCallCount() const
    {
        return m_DrawCallCount;
    }

    void SDLRendererAPI::Shutdown()
    {
    }

    RendererBackend SDLRendererAPI::GetBackend() const
    {
        return RendererBackend::SDL;
    }
}