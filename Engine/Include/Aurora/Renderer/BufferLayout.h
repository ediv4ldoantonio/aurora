#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <initializer_list>

namespace Aurora
{
    enum class ShaderDataType : uint8_t
    {
        None = 0,

        Float,
        Float2,
        Float3,
        Float4,

        Int,
        Int2,
        Int3,
        Int4,

        UByte4,

        Bool
    };

    struct BufferElement
    {
        std::string Name;

        ShaderDataType Type =
            ShaderDataType::None;

        size_t Size = 0;

        size_t Offset = 0;

        bool Normalized = false;

        BufferElement(
            ShaderDataType type,
            const std::string &name,
            bool normalized = false)
            : Name(name),
              Type(type),
              Normalized(normalized)
        {
        }

        uint32_t GetComponentCount() const;
    };

    class BufferLayout
    {
    public:
        BufferLayout() = default;

        BufferLayout(
            std::initializer_list<BufferElement> elements);

        const std::vector<BufferElement> &
        GetElements() const;

        size_t GetStride() const;

    private:
        void CalculateOffsetsAndStride();

        size_t GetShaderDataTypeSize(
            ShaderDataType type);

    private:
        std::vector<BufferElement>
            m_Elements;

        size_t m_Stride = 0;
    };
}