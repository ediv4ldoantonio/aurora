#pragma once

#include "Aurora/Renderer/Shader.h"

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

    private:
        int GetUniformLocation(
            const std::string &name) const;

        uint32_t CompileShader(
            uint32_t type,
            const std::string &source);

    private:
        uint32_t m_RendererID = 0;
    };
}