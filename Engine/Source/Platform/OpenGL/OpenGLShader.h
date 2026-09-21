#pragma once

#include "Aurora/Renderer/Shader.h"
#include "Aurora/Renderer/SpriteBatch.h"

#include <string>
#include <unordered_map>

#include <glad/gl.h>

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

        void SetVector2(
            const std::string &name,
            const Vector2 &value) override;

    private:
        int GetUniformLocation(
            const std::string &name) const;

        uint32_t CompileShader(
            uint32_t type,
            const std::string &source);

        GLint GetUniformLocationCached(
            const std::string &name);

        uint32_t m_RendererID = 0;

        std::unordered_map<std::string, GLint>
            m_UniformLocationCache;
    };
}