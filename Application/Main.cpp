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

	//create frameBuffer texture

	auto texture = std::make_shared<neu::Texture>();

	texture->CreateTexture(512, 512);

	neu::g_resources.add<neu::Texture>("fb_texture", texture);

	//create frameBuffer

	auto framebuffer = neu::g_resources.Get<neu::Framebuffer>("framebuffer", "fb_texture");

	framebuffer->Unbind();

	// load scene 

	auto scene = std::make_unique<neu::Scene>();

	rapidjson::Document document;
	
	std::string workPlz = "scenes/rtt.scn";

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

	glm::vec3 rot{ 0,0,0 };

	float interpolation = 1;

	float refractionIndex = 1;

	float x = 0;

	while (!quit){

		neu::Engine::Instance().Update();

		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyDown(neu::key_escape) == neu::InputSystem::State::Pressed) quit = true;

		auto actor = scene->getActorFromName("Model");
		
		auto actor2 = scene->getActorFromName("Scenery");

		auto actor3 = scene->getActorFromName("Light");

		auto actor4 = scene->getActorFromName("Skybox");
		
		if (actor){

			// move light using sin wave 

			actor->m_transform.rotation = Math::EulerToQuaternion(rot);

		}

		auto material = neu::g_resources.Get<neu::Material>("materials/multi.mtrl");

		auto program = neu::g_resources.Get<neu::Program>("shaders/Fx/refrac.prog");

		if(program){ 

			program->Use();
		
			program->SetUniform("i", interpolation);

			program->SetUniform("ri", refractionIndex);
		
		}

		ImGui::Begin("Transform");

		ImGui::DragFloat3("Rotation", &rot[0]);

		ImGui::DragFloat("Refraction index", &interpolation, 0.01f, 0, 1);

		ImGui::DragFloat("Refraction index", &refractionIndex, 0.05f, 1, 3.2);

		ImGui::End();

		scene->Update();

		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });

		{
			auto actor = scene->getActorFromName("RTT");
			
			if (actor){
			
				actor->setActive(false);
			
			}

		}

		//render pass 1 to frame buffer

		glViewport(0, 0, 512, 512);

		framebuffer->Bind();

		neu::g_renderer.BeginFrame();

		scene->PreRender(neu::g_renderer);

		scene->Render(neu::g_renderer);

		framebuffer->Unbind();

		{
			auto actor = scene->getActorFromName("RTT");

			if (actor) {

				actor->setActive(true);

			}

		}

		//render pass 2 to screen

		glViewport(0, 0, 800, 600);

		neu::g_renderer.BeginFrame();

		scene->PreRender(neu::g_renderer);

		scene->Render(neu::g_renderer);

		neu::g_gui.Draw();

		neu::g_renderer.EndFrame();

		neu::g_gui.EndFrame();
	
	}

	scene->removeAll();

	neu::Engine::Instance().Shutdown();

	return 0;

}
