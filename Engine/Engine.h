#pragma once

#include "Serialization/Json.h"

#include "Core/File.h"

#include "Core/Memory.h"

#include "Core/Time.h"

#include "Core/Logger.h"

#include "Math/Random.h"

#include "Math/MathUtils.h"

#include "FrameWork/Scene.h"

#include "FrameWork/Game.h"

#include "FrameWork/Singleton.h"

#include "FrameWork/Factory.h"

#include "FrameWork/EventManager.h"

#include "Renderer/Font.h"

#include "Renderer/Text.h"

#include "Model.h"

#include "Input/InputSystem.h"

#include "Components/PlayerComponent.h"

#include "Components/SpriteComponent.h"

#include "Components/AudioComponent.h"

#include "Components/PhysicsComponent.h"

#include "Components/ModelComponent.h"

#include "Components/TextComponent.h"

#include "Components/SpriteAnimeComponent.h"

#include "Components/RBPhysicsComponent.h"

#include "Components/CollisionComponent.h"

#include "Components/TilemapComponent.h"

#include "Components/CharacterComponent.h"

#include "Components/CameraComponent.h"

#include "Renderer/Renderer.h"

#include "Audio/AudioSystem.h"

#include "Resource/ResourceMagager.h"

#include "Physics/PhysicsSystem.h"

#include <memory>

#include <iostream>

#include <list>

#include <algorithm>

#include <variant>

namespace neu {

	extern InputSystem g_inputSystem;

	extern Renderer g_renderer;

	extern Time g_time;

	extern Scene g_scene;

	extern AudioSystem g_audio;

	extern ResourceManager g_resources;

	extern PhysicsSystem g_physicsSystem;

	extern EventManager g_eventManager;

	class Engine : public Singleton<Engine> {

	public:

		void Initialize();

		void Shutdown();

		void Update();

		void Register();

	};

}

