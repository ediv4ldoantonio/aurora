#include "OpenGLShader.h"

#include <glad/gl.h>

#include <stdexcept>
#include <string>
#include <vector>

namespace Aurora
{
    OpenGLShader::OpenGLShader(
        const std::string &vertexSource,
        const std::string &fragmentSource)
    {
        const uint32_t vertexShader =
            CompileShader(
                GL_VERTEX_SHADER,
                vertexSource);

        const uint32_t fragmentShader =
            CompileShader(
                GL_FRAGMENT_SHADER,
                fragmentSource);

        m_RendererID = glCreateProgram();

        glAttachShader(
            m_RendererID,
            vertexShader);

        glAttachShader(
            m_RendererID,
            fragmentShader);

        glLinkProgram(m_RendererID);

        GLint linked = GL_FALSE;

        glGetProgramiv(
            m_RendererID,
            GL_LINK_STATUS,
            &linked);

        if (linked == GL_FALSE)
        {
            GLint length = 0;

            glGetProgramiv(
                m_RendererID,
                GL_INFO_LOG_LENGTH,
                &length);

            std::vector<char> log(
                static_cast<size_t>(length));

            glGetProgramInfoLog(
                m_RendererID,
                length,
                nullptr,
                log.data());

            glDeleteProgram(m_RendererID);
            m_RendererID = 0;

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            throw std::runtime_error(
                "OpenGL shader program linking failed: " +
                std::string(log.data()));
        }

        glDetachShader(
            m_RendererID,
            vertexShader);

        glDetachShader(
            m_RendererID,
            fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        if (m_RendererID != 0)
        {
            glDeleteProgram(m_RendererID);
            m_RendererID = 0;
        }
    }

    uint32_t OpenGLShader::CompileShader(
        uint32_t type,
        const std::string &source)
    {
        const uint32_t shader =
            glCreateShader(type);

        const char *sourceData =
            source.c_str();

        glShaderSource(
            shader,
            1,
            &sourceData,
            nullptr);

        glCompileShader(shader);

        GLint compiled = GL_FALSE;

        glGetShaderiv(
            shader,
            GL_COMPILE_STATUS,
            &compiled);

        if (compiled == GL_FALSE)
        {
            GLint length = 0;

            glGetShaderiv(
                shader,
                GL_INFO_LOG_LENGTH,
                &length);

            std::vector<char> log(
                static_cast<size_t>(length));

            glGetShaderInfoLog(
                shader,
                length,
                nullptr,
                log.data());

            glDeleteShader(shader);

            const std::string stage =
                type == GL_VERTEX_SHADER
                    ? "vertex"
                    : "fragment";

            throw std::runtime_error(
                "OpenGL " + stage +
                " shader compilation failed: " +
                std::string(log.data()));
        }

        return shader;
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    int OpenGLShader::GetUniformLocation(
        const std::string &name) const
    {
        return static_cast<uint32_t>(
            glGetUniformLocation(
                m_RendererID,
                name.c_str()));
    }

    void OpenGLShader::SetInt(
        const std::string &name,
        int value)
    {
        glUniform1i(
            GetUniformLocation(name),
            value);
    }

    void OpenGLShader::SetFloat(
        const std::string &name,
        float value)
    {
        glUniform1f(
            GetUniformLocation(name),
            value);
    }

    void OpenGLShader::SetMatrix4(
        const std::string &name,
        const float *value)
    {
        glUniformMatrix4fv(
            GetUniformLocation(name),
            1,
            GL_TRUE,
            value);
    }
}