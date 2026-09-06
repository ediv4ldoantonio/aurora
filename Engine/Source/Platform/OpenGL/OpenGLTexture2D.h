#pragma once

#include "Aurora/Renderer/Texture2D.h"

namespace Aurora
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        explicit OpenGLTexture2D(
            const std::string &path);

        ~OpenGLTexture2D() override;

        void Bind(uint32_t slot = 0) const override;

        void Unbind() const override;

        uint32_t GetWidth() const override;
        uint32_t GetHeight() const override;

        bool IsLoaded() const override;

        const std::string &
        GetPath() const override;

    private:
        uint32_t m_RendererID = 0;

        uint32_t m_Width = 0;
        uint32_t m_Height = 0;

        int m_Channels = 0;

        std::string m_Path;
    };
}