#pragma once

#include <memory>
#include <string>

namespace Aurora
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetInt(
            const std::string &name,
            int value) = 0;

        virtual void SetFloat(
            const std::string &name,
            float value) = 0;

        virtual void SetMatrix4(
            const std::string &name,
            const float *value) = 0;

        static std::shared_ptr<Shader>
        Create(
            const std::string &vertexSource,
            const std::string &fragmentSource);
    };
}