#include "Engine.h"

#include <iostream> 

#define POST_PROCESS 

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

	texture->CreateTexture(1024, 1024);

	neu::g_resources.add<neu::Texture>("fb_texture", texture);

	//create frameBuffer

	auto framebuffer = neu::g_resources.Get<neu::Framebuffer>("framebuffer", "fb_texture");

	framebuffer->Unbind();

	// load scene 

	auto scene = std::make_unique<neu::Scene>();

	rapidjson::Document document;
	
	std::string workPlz = "scenes/final.scn";

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

		auto program1 = neu::g_resources.Get<neu::Program>("shaders/Fx/refrac.prog");

		if(program1){ 

			program1->Use();
		
			//program1->SetUniform("i", interpolation);

			//program1->SetUniform("ri", refractionIndex);
		
		}

		//auto program = neu::g_resources.Get<neu::Program>("shaders/postprocess/postprocess.prog");
		//
		//if (program){

		//	program->Use();
		//	
		//	program->SetUniform("offset", neu::g_time.time);
		//
		//}

		ImGui::Begin("Transform");

		ImGui::DragFloat3("Rotation", &rot[0]);

		ImGui::DragFloat("Refraction index", &interpolation, 0.01f, 0, 1);

		ImGui::DragFloat("Refraction index", &refractionIndex, 0.05f, 1, 3.2);

		ImGui::End();

		scene->Update();

#ifdef POST_PROCESS 
		
		// don't draw post process actor when rendering to the framebuffer 
		
		{
		
			auto actor = scene->getActorFromName("PostProcess");
			
			if (actor){

				actor->setActive(false);

			}

		}

		// render pass 1 (render scene to framebuffer) 

		neu::g_renderer.SetViewport(0, 0, framebuffer -> GetSize().x, framebuffer->GetSize().y);

		framebuffer->Bind();
		
		neu::g_renderer.BeginFrame();
		
		scene->PreRender(neu::g_renderer);
		
		scene->Render(neu::g_renderer);
		
		framebuffer->Unbind();

		// render pass 2 (render to screen) 
		
		neu::g_renderer.RestoreViewport();
		
		neu::g_renderer.BeginFrame();
		
		scene->PreRender(neu::g_renderer);

		// draw only the post process actor to the screen 
		
		{
		
			auto actor = scene->getActorFromName("PostProcess");
			
			if (actor){

				actor->setActive(true);
				
				actor->Draw(neu::g_renderer);
			
			}

		}

#else 

		neu::g_renderer.BeginFrame();
		
		scene->PreRender(neu::g_renderer);
		
		scene->Render(neu::g_renderer);

#endif // POST_PROCESS 

		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });

		{
			auto actor = scene->getActorFromName("RTT");
			
			if (actor){
			
				actor->setActive(false);
			
			}

		}



		//render pass 1 to frame buffer

		neu::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		
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

		neu::g_renderer.RestoreViewport();

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
