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

	while (!quit){

		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyDown(neu::key_escape) == neu::InputSystem::State::Pressed) quit = true;

		auto actor = scene->getActorFromName("Spot");
		
		auto actor2 = scene->getActorFromName("Scenery");


		if (actor){

			//actor->m_transform.rotation.y += neu::g_time.deltaTime * 90.0f;

		}

		auto material = neu::g_resources.Get<neu::Material>("materials/multi.mtrl");

		if (material) {

			/*material->uv_offset.x += neu::g_time.deltaTime * 0.3f;

			material->uv_offset.y -= neu::g_time.deltaTime * 0.15f;*/

		}

		scene->Update();
		

		if (neu::g_inputSystem.GetKeyState(neu::key_d) == neu::InputSystem::State::Held){

			cameraPosition.x -= speed * neu::g_time.deltaTime;
	
			//std::string str{ "Camera Position: x:" };
			
			//str.append(std::to_string(cameraPosition.x)).append(" y:").append(std::to_string(cameraPosition.y)).append(" z:").append(std::to_string(cameraPosition.z));
			
			//LOG(str.c_str());
		
		}

		if (neu::g_inputSystem.GetKeyState(neu::key_a) == neu::InputSystem::State::Held) {

			cameraPosition.x += speed * neu::g_time.deltaTime;

		}

		if (neu::g_inputSystem.GetKeyState(neu::key_space) == neu::InputSystem::State::Held) {

			cameraPosition.z -= speed * neu::g_time.deltaTime;

		}

		if (neu::g_inputSystem.GetKeyState(neu::key_shift) == neu::InputSystem::State::Held) {

			cameraPosition.z += speed * neu::g_time.deltaTime;

		}

		if (neu::g_inputSystem.GetKeyState(neu::key_w) == neu::InputSystem::State::Held) {

			cameraPosition.y -= speed * neu::g_time.deltaTime;

		}

		if (neu::g_inputSystem.GetKeyState(neu::key_s) == neu::InputSystem::State::Held) {

			cameraPosition.y += speed * neu::g_time.deltaTime;

		}



		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });

		neu::g_renderer.BeginFrame();

		scene->Draw(neu::g_renderer);

		neu::g_renderer.EndFrame();
	
	}

	scene->removeAll();

	neu::Engine::Instance().Shutdown();

	return 0;

}
