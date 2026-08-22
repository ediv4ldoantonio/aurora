#include "SDLTexture2D.h"
#include "Aurora/Core/Logger.h"
#include "Aurora/Renderer/Renderer2D.h"
#include "Aurora/Renderer/RendererAPI.h"
#include <SDL3_image/SDL_image.h>

namespace Aurora
{
    SDLTexture2D::SDLTexture2D(
        const std::string &path)
        : m_Path(path)
    {
        SDL_Surface *surface =
            IMG_Load(path.c_str());

        if (!surface)
        {
            AURORA_LOG_ERROR("Failed to load texture: ", path.c_str());
            return;
        }

        m_Width = surface->w;
        m_Height = surface->h;

        SDL_Renderer *renderer =
            static_cast<SDL_Renderer *>(
                Renderer2D::GetRendererAPI()
                    ->GetNativeRenderer());

        m_Texture =
            SDL_CreateTextureFromSurface(
                renderer,
                surface);

        if (!m_Texture)
        {
            AURORA_LOG_ERROR(
                "Failed to create GPU texture.");

            SDL_DestroySurface(surface);

            return;
        }

        SDL_SetTextureBlendMode(
            m_Texture,
            SDL_BLENDMODE_BLEND);

        SDL_DestroySurface(surface);
    }

    SDLTexture2D::~SDLTexture2D()
    {
        if (m_Texture)
            SDL_DestroyTexture(m_Texture);
    }

    bool SDLTexture2D::IsLoaded() const
    {
        return m_Texture != nullptr;
    }

    uint32_t SDLTexture2D::GetWidth() const
    {
        return m_Width;
    }

    uint32_t SDLTexture2D::GetHeight() const
    {
        return m_Height;
    }

    const std::string &
    SDLTexture2D::GetPath() const
    {
        return m_Path;
    }

    SDL_Texture *SDLTexture2D::GetNativeTexture()
    {
        return m_Texture;
    }
}