
#include "Engine.h"

namespace neu {

	InputSystem g_inputSystem;

	Renderer g_renderer;

	Time g_time;

	Scene g_scene;

	AudioSystem g_audio;

	ResourceManager g_resources;

	PhysicsSystem g_physicsSystem;

	EventManager g_eventManager;

	void Engine::Initialize(){

		g_renderer.Initialize();
		
		g_inputSystem.Initialize();
		
		g_audio.Initialize();

		g_resources.initialize();
		
		g_physicsSystem.Initialize();
		
		g_eventManager.Initialize();
	
	}

	void Engine::Update(){

		g_time.Tick();
		
		g_eventManager.Update();
		
		g_physicsSystem.Update();
		
		g_inputSystem.Update();
		
		g_audio.Update();
	
	}

	void Engine::Shutdown(){

		Factory::Instance().Shutdown();

		g_eventManager.Shutdown();
		
		g_physicsSystem.Shutdown();
		
		g_resources.shutDown();
		
		g_inputSystem.Shutdown();
		
		g_audio.Shutdown();
		
		g_renderer.Shutdown();
	
	}

	void Engine::Register(){

		REGISTER_CLASS(Actor);
		
		REGISTER_CLASS(AudioComponent);
		
		REGISTER_CLASS(ModelComponent);

		REGISTER_CLASS(TextComponent);
		
		REGISTER_CLASS(PhysicsComponent);

		REGISTER_CLASS(RBPhysicsComponent);

		REGISTER_CLASS(CollisionComponent);
		
		REGISTER_CLASS(PlayerComponent);
		
		REGISTER_CLASS(SpriteComponent);

		REGISTER_CLASS(SpriteAnimeComponent);

		REGISTER_CLASS(TilemapComponent);

		REGISTER_CLASS(CameraComponent);

		REGISTER_CLASS(CameraController);
		
	}

}
