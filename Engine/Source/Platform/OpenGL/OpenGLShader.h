#pragma once

#include "Aurora/Renderer/Shader.h"
#include "Aurora/Renderer/SpriteBatch.h"

namespace Aurora
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(
            const std::string &vertexSource,
            const std::string &fragmentSource);

        ~OpenGLShader() override;

        void Bind() const override;
        void Unbind() const override;

        void SetInt(
            const std::string &name,
            int value) override;

        void SetFloat(
            const std::string &name,
            float value) override;

        void SetMatrix4(
            const std::string &name,
            const float *value) override;

        void SetVector4(
            const std::string &name,
            float x,
            float y,
            float z,
            float w) override;

    private:
        int GetUniformLocation(
            const std::string &name) const;

        uint32_t CompileShader(
            uint32_t type,
            const std::string &source);

        uint32_t m_RendererID = 0;
    };
}