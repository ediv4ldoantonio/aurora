#include "Aurora/Renderer/BufferLayout.h"

namespace Aurora
{
    uint32_t BufferElement::GetComponentCount() const
    {
        switch (Type)
        {
        case ShaderDataType::Float:
            return 1;

        case ShaderDataType::Float2:
            return 2;

        case ShaderDataType::Float3:
            return 3;

        case ShaderDataType::Float4:
            return 4;

        case ShaderDataType::Int:
            return 1;

        case ShaderDataType::Int2:
            return 2;

        case ShaderDataType::Int3:
            return 3;

        case ShaderDataType::Int4:
            return 4;

        case ShaderDataType::UByte4:
            return 4;

        case ShaderDataType::Bool:
            return 1;

        case ShaderDataType::None:
            break;
        }

        return 0;
    }

    size_t BufferLayout::GetShaderDataTypeSize(
        ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:
            return sizeof(float);

        case ShaderDataType::Float2:
            return sizeof(float) * 2;

        case ShaderDataType::Float3:
            return sizeof(float) * 3;

        case ShaderDataType::Float4:
            return sizeof(float) * 4;

        case ShaderDataType::Int:
            return sizeof(int32_t);

        case ShaderDataType::Int2:
            return sizeof(int32_t) * 2;

        case ShaderDataType::Int3:
            return sizeof(int32_t) * 3;

        case ShaderDataType::Int4:
            return sizeof(int32_t) * 4;

        case ShaderDataType::UByte4:
            return sizeof(uint8_t) * 4;

        case ShaderDataType::Bool:
            return sizeof(bool);

        case ShaderDataType::None:
            break;
        }

        return 0;
    }

    BufferLayout::BufferLayout(
        std::initializer_list<BufferElement> elements)
        : m_Elements(elements)
    {
        CalculateOffsetsAndStride();
    }

    void BufferLayout::CalculateOffsetsAndStride()
    {
        size_t offset = 0;

        m_Stride = 0;

        for (auto &element : m_Elements)
        {
            element.Size =
                GetShaderDataTypeSize(
                    element.Type);

            element.Offset =
                offset;

            offset +=
                element.Size;

            m_Stride +=
                element.Size;
        }
    }

    const std::vector<BufferElement> &
    BufferLayout::GetElements() const
    {
        return m_Elements;
    }

    size_t BufferLayout::GetStride() const
    {
        return m_Stride;
    }

}