#include "Engine.h"

#include <iostream> 

int main(){

	kronk::innitMemory();

	neu::Engine::Instance().Initialize();
	
	neu::Engine::Instance().Register();

	neu::g_renderer.CreateWindow("Neumont", 800, 600);

	bool quit = false;
	
	while (!quit){

		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyDown(neu::key_escape) == neu::InputSystem::State::Pressed) quit = true;

		neu::g_renderer.BeginFrame();

		neu::g_renderer.EndFrame();
	
	}

	neu::Engine::Instance().Shutdown();

}
