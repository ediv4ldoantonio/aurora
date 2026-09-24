#pragma once

// Core
#include "Aurora/Core/Application.h"
#include "Aurora/Core/Layer.h"
#include "Aurora/Core/LayerStack.h"
#include "Aurora/Core/Logger.h"
#include "Aurora/Core/Time.h"
#include "Aurora/Core/UUID.h"
#include "Aurora/Core/Window.h"

// Math
#include "Aurora/Math/Matrix4.h"
#include "Aurora/Math/Transform.h"
#include "Aurora/Math/Vector2.h"

// Events & input
#include "Aurora/Events/ApplicationEvents.h"
#include "Aurora/Events/Event.h"
#include "Aurora/Events/EventDispatcher.h"
#include "Aurora/Events/KeyEvents.h"
#include "Aurora/Input/Input.h"
#include "Aurora/Input/KeyCodes.h"

// Assets
#include "Aurora/Assets/Asset.h"
#include "Aurora/Assets/AssetManager.h"

// Renderer
#include "Aurora/Renderer/Camera2D.h"
#include "Aurora/Renderer/Color.h"
#include "Aurora/Renderer/Renderer2D.h"
#include "Aurora/Renderer/Texture2D.h"

// ECS, scene & systems
#include "Aurora/ECS/Registry.h"
#include "Aurora/ECS/System.h"
#include "Aurora/ECS/SystemManager.h"
#include "Aurora/ECS/View.h"
#include "Aurora/Scene/Components/Component.h"
#include "Aurora/Scene/Entity.h"
#include "Aurora/Scene/Scene.h"
#include "Aurora/Systems/RenderSystem.h"
#include "Aurora/Systems/ScriptSystem.h"
#include "Aurora/Systems/TransformSystem.h"
