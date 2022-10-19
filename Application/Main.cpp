#include "Engine.h"

#include <iostream> 

float vertices[] = {

	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	
	 -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	
	 -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	
	 -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	
	 -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	
	 -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	
	 -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	
	 -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	
	 -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	
	 -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	
	 -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	
	 -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	
	0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	
	0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	
	 -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	
	 -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f

};

int main(int argc, char** argv){

	LOG("Application Started . . .");

	kronk::innitMemory();

	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	
	neu::Engine::Instance().Register();

	LOG("Engine Initialized . . . ");

	neu::g_renderer.CreateWindow("Neumont", 800, 600, false);

	LOG("Window Initialized . . .");

	// create vertex buffer

	std::shared_ptr<neu::VertexBuffer> vb = neu::g_resources.Get<neu::VertexBuffer>("box");

	vb->CreateVertexBuffer(sizeof(vertices), 36, vertices);

	vb->SetAttribute(0, 3, 8 * sizeof(float), 0);

	vb->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));

	vb->SetAttribute(2, 3, 8 * sizeof(float), 6 * sizeof(float));

	// create shader

	std::shared_ptr<neu::Shader> vs = neu::g_resources.Get<neu::Shader>("shaders/basic.vert", GL_VERTEX_SHADER);
	
	std::shared_ptr<neu::Shader> fs = neu::g_resources.Get<neu::Shader>("shaders/basic.frag", GL_FRAGMENT_SHADER);

	// create program

	std::shared_ptr<neu::Program> program = neu::g_resources.Get<neu::Program>("shaders/basic.prog", GL_PROGRAM);

	program->Link();

	program->Use();
	
	glm::mat4 model{ 1 };

	glm::mat4 projection = glm::perspective(45.0f, neu::g_renderer.GetWidth() / (float)neu::g_renderer.GetHeight(), 0.01f, 100.0f);

	glm::vec3 cameraPosition = glm::vec3{ 0,0,2 };

	// create material 

	std::shared_ptr<neu::Material> material = neu::g_resources.Get<neu::Material>("materials/box.mtrl");

	material->Bind();

	material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });

	material->GetProgram()->SetUniform("scale", 0.5f);

	//material->GetProgram()->SetUniform("scale", std::sin(neu::g_time.time * 3));
	
	material->GetProgram()->SetUniform("transform", model);

	//create texture

	std::shared_ptr<neu::Texture> texture1 = neu::g_resources.Get<neu::Texture>("textures/box.png");

	std::shared_ptr<neu::Texture> texture2 = neu::g_resources.Get<neu::Texture>("textures/llama.png");

	texture1->Bind();

	bool quit = false;

	float speed = 3;

	while (!quit){

		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyDown(neu::key_escape) == neu::InputSystem::State::Pressed) quit = true;
	
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

		model = glm::eulerAngleXYZ(neu::g_time.time * -2, neu::g_time.time * 3, 0.0f);

		glm::mat4 mvp = projection * view * model;

		//program->SetUniform("scale", std::sin(neu::g_time.time * 3));

		program->SetUniform("mvp", mvp);

		neu::g_renderer.BeginFrame();

		vb->Draw();

		neu::g_renderer.EndFrame();
	
	}

	neu::Engine::Instance().Shutdown();

	return 0;

}
