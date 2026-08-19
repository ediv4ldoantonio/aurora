#include "Aurora/Scene/Scene.h"
#include "Aurora/Scene/Entity.h"
#include "Aurora/Renderer/Renderer2D.h"
#include "Aurora/Renderer/RenderCommand.h"
#include "Aurora/Scene/Components/SpriteComponent.h"
#include "Aurora/Scene/Components/TransformComponent.h"
#include "Aurora/Scene/Components/ScriptComponent.h"
#include "Aurora/Scene/Components/IDComponent.h"
#include "Aurora/Scene/Components/NameComponent.h"
#include "Aurora/Scene/Components/RelationshipComponent.h"
#include "Aurora/Systems/RenderSystem.h"
#include "Aurora/Systems/ScriptSystem.h"
#include "Aurora/Systems/TransformSystem.h"
#include "Aurora/Events/EventDispatcher.h"
#include "Aurora/Events/ApplicationEvents.h"
#include "Aurora/Core/Logger.h"
#include "Aurora/Input/Input.h"

#include <algorithm>

namespace Aurora
{
    using EntityID = uint32_t;

    Scene::Scene()
    {
        m_Camera.SetViewportSize(
            {1280.0f, 720.0f});

        m_Camera.SetPosition(
            {0.0f, 0.0f});

        m_Camera.SetZoom(
            1.0f);

        m_Camera.SetRotation(0);

        m_SystemManager
            .AddSystem<RenderSystem>();

        m_SystemManager
            .AddSystem<ScriptSystem>();

        m_SystemManager
            .AddSystem<TransformSystem>();
    }

    Entity Scene::CreateEntity(const std::string &name)
    {
        Entity entity = m_Registry.CreateEntity(this);

        UUID uuid = entity.AddComponent<IDComponent>().ID;
        entity.AddComponent<NameComponent>(name);
        entity.AddComponent<TransformComponent>();
        entity.AddComponent<RelationshipComponent>();

        m_EntityMap.emplace(
            uuid,
            entity.GetID());

        return entity;
    }

    void Scene::OnUpdate(
        float deltaTime)
    {
        UpdateCamera(deltaTime);

        m_SystemManager.Update(
            m_Registry,
            deltaTime);

        ProcessDestroyQueue();
    }

    void Scene::OnRender()
    {
        Renderer2D::SetCamera(
            &m_Camera);
        m_SystemManager.Render(
            m_Registry);
    }

    void Scene::OnEvent(Event &event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<WindowResizeEvent>(
            [this](WindowResizeEvent &e)
            {
                m_Camera.SetViewportSize(
                    Vector2(
                        static_cast<float>(e.GetWidth()),
                        static_cast<float>(e.GetHeight())));

                RenderCommand::SetViewport(0, 0, e.GetWidth(), e.GetHeight());

                return false;
            });
    }

    void Scene::SetParent(
        Entity child,
        Entity parent)
    {
        RemoveParent(child);

        auto &childRelationship =
            child.GetComponent<RelationshipComponent>();

        auto &parentRelationship =
            parent.GetComponent<RelationshipComponent>();

        childRelationship.Parent = parent;

        parentRelationship.Children.push_back(child);
    }

    void Scene::RemoveParent(
        Entity child)
    {
        auto &childRelationship =
            child.GetComponent<RelationshipComponent>();

        if (!childRelationship.Parent)
            return;

        auto &parentRelationship =
            childRelationship.Parent
                .GetComponent<RelationshipComponent>();

        auto &children =
            parentRelationship.Children;

        children.erase(
            std::remove(
                children.begin(),
                children.end(),
                child),
            children.end());

        childRelationship.Parent = {};
    }

    void Scene::DestroyEntity(Entity entity)
    {
        m_DestroyQueue.push_back(entity);
    }

    void Scene::ProcessDestroyQueue()
    {
        for (EntityID id : m_DestroyQueue)
        {
            Entity entity(
                id,
                &m_Registry,
                this);

            DestroyEntityNow(entity);
        }

        m_DestroyQueue.clear();
    }

    void Scene::DestroyEntityNow(Entity entity)
    {
        if (!entity.IsValid())
            return;

        UUID uuid =
            entity.GetComponent<IDComponent>().ID;

        m_EntityMap.erase(uuid);

        //---------------------------------------------------
        // Destroy children first
        //---------------------------------------------------

        if (entity.HasComponent<RelationshipComponent>())
        {
            auto &relationship =
                entity.GetComponent<RelationshipComponent>();

            // Copy because recursion modifies the vector
            std::vector<Entity> children =
                relationship.Children;

            for (auto child : children)
            {
                DestroyEntityNow(child);
            }
        }

        //---------------------------------------------------
        // Notify script
        //---------------------------------------------------

        if (entity.HasComponent<ScriptComponent>())
        {
            auto &script =
                entity.GetComponent<ScriptComponent>();

            if (script.Instance)
            {
                script.Instance->OnDestroy();

                script.Instance.reset();
            }
        }

        //---------------------------------------------------
        // Remove from parent
        //---------------------------------------------------

        RemoveParent(entity);

        //---------------------------------------------------
        // Finally remove entity
        //---------------------------------------------------

        m_Registry.DestroyEntity(entity.GetID());
    }

    Entity Scene::GetEntityByUUID(UUID uuid)
    {
        auto it = m_EntityMap.find(uuid);

        if (it == m_EntityMap.end())
            return {};

        return Entity(
            it->second,
            &m_Registry,
            this);
    }

    Camera2D &Scene::GetCamera()
    {
        return m_Camera;
    }

    void Scene::UpdateCamera(float dt)
    {
        constexpr float cameraSpeed = 3000.0f;
        float zoom = m_Camera.GetZoom();

        Vector2 movement(0.0f, 0.0f);

        if (Input::IsKeyPressed(Aurora::Key::A))
        {
            movement.x -= cameraSpeed;
        }

        if (Input::IsKeyPressed(Aurora::Key::D))
        {
            movement.x += cameraSpeed;
        }

        if (Input::IsKeyPressed(Aurora::Key::W))
        {
            movement.y -= cameraSpeed;
        }

        if (Input::IsKeyPressed(Aurora::Key::S))
        {
            movement.y += cameraSpeed;
        }

        if (Input::IsKeyPressed(Aurora::Key::Q))
        {
            zoom -= 1.0f * dt;
        }

        if (Input::IsKeyPressed(Aurora::Key::E))
        {
            zoom += 1.0f * dt;
        }

        zoom = std::max(0.1f, zoom);

        m_Camera.SetZoom(zoom);

        m_Camera.SetPosition(
            m_Camera.GetPosition() + movement * dt);
    }
}