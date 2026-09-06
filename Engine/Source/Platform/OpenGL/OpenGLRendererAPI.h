#pragma once

#include "Aurora/Renderer/RendererAPI.h"
#include "Aurora/Renderer/RendererBackend.h"
#include "Aurora/Renderer/Shader.h"
#include "Aurora/Renderer/Material.h"
#include "Aurora/Renderer/VertexArray.h"
#include "Aurora/Renderer/VertexBuffer.h"
#include "Aurora/Renderer/IndexBuffer.h"
#include "Aurora/Renderer/BlendMode.h"

#include <memory>
#include <stdexcept>

namespace Aurora
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void Init() override;

        void BeginFrame() override;

        void EndFrame() override;

        void Shutdown() override;

        void DrawSprite(
            const SpriteDrawCommand &command) override;

        void DrawIndexed(
            const std::shared_ptr<VertexArray> &vertexArray,
            uint32_t indexCount) override;

        void Clear(const Color &color) override;

        void SetViewport(
            int x,
            int y,
            int width,
            int height) override;

        void DrawSpriteBatch(
            const SpriteBatch &batch) override;

        void *GetNativeRenderer() override;

        RendererBackend GetBackend() const override;

        void SetViewProjection(
            const Matrix4 &viewProjection) override;

    private:
        void UploadMaterialState(
            const SpriteBatch &batch);

        void BindBatchMaterials(
            const SpriteBatch &batch);

        void UploadBatchVertices(
            const SpriteBatch &batch);

        void ApplyBlendMode(
            BlendMode mode);

        std::shared_ptr<VertexArray> m_SpriteVertexArray;
        std::shared_ptr<VertexBuffer> m_SpriteVertexBuffer;
        std::shared_ptr<IndexBuffer> m_SpriteIndexBuffer;
        std::shared_ptr<Shader> m_SpriteShader;
    };
}
