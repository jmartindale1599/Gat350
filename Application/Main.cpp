#include "Engine.h"

#include <iostream> 

int main(int argc, char** argv){

	LOG("Application Started . . .");

	kronk::innitMemory();

	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	
	neu::Engine::Instance().Register();

	LOG("Engine Initialized . . . ");

	neu::g_renderer.CreateWindow("Neumont", 800, 600, false);

	LOG("Window Initialized . . .");

	neu::g_gui.Initialize(neu::g_renderer);

	// load scene 

	auto scene = std::make_unique<neu::Scene>();

	rapidjson::Document document;
	
	std::string workPlz = "scenes/texture.scn";

	bool success = true; // neu::json::Load("scenes/basicLit.scn", document);
	
	if (!success){

		LOG("error loading scene file %s.", workPlz);
	
	}else{

		scene->Create(workPlz);
		
		scene->Initialize();
	
	}

	glm::vec3 cameraPosition = glm::vec3{ 0,0,2 };

	bool quit = false;

	float speed = 3;

	glm::vec3 pos{ 0,0,0 };

	float x = 0;

	while (!quit){

		neu::Engine::Instance().Update();

		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyDown(neu::key_escape) == neu::InputSystem::State::Pressed) quit = true;

		auto actor = scene->getActorFromName("Spot");
		
		auto actor2 = scene->getActorFromName("Scenery");

		auto actor3 = scene->getActorFromName("Light");
		
		if (actor3){

			// move light using sin wave 
			
			actor3->m_transform.position.x = std::sin(neu::g_time.time) * 2;

		}

		if (actor){

			//actor->m_transform.rotation.y += neu::g_time.deltaTime * 60.0f;

			actor->m_transform.rotation.x -= x;

		}

		auto material = neu::g_resources.Get<neu::Material>("materials/multi.mtrl");

		ImGui::Begin("Hello");

		ImGui::Button("Press ME");

		ImGui::SliderFloat("X", &pos.x, -5.0f, 5.0f);

		ImGui::End();

		scene->Update();

		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });

		neu::g_renderer.BeginFrame();

		scene->Draw(neu::g_renderer);

		neu::g_gui.Draw();

		neu::g_renderer.EndFrame();

		neu::g_gui.EndFrame();
	
	}

	scene->removeAll();

	neu::Engine::Instance().Shutdown();

	return 0;

}
