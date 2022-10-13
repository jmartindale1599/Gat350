#include "Engine.h"

#include <iostream> 

float points[] = {

  -1, -1,  0,
   
  -1,  0,  0,
  
  0, -1,  0,

  0, -1, 0,

  0, 0, 0,

  -1, 0, 0

};

glm::vec3 colors[] = { //change it to glm namespace

	{0, 0, 1}, // rgb
	
	{1, 0, 1},
	
	{0, 1, 1},
	
	{1, 0, 0},

	{0, 1, 0},

	{1, 1, 0}

};

glm::vec2 textCoords[]{

	{0,0},

	{0,1},

	{1,0},

	{0,1},

	{1,1},

	{1,0}

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

	GLuint pvbo = 0;
	
	glGenBuffers(1, &pvbo);
	
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint cvbo = 0;

	glGenBuffers(1, &cvbo);

	glBindBuffer(GL_ARRAY_BUFFER, cvbo);

	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), colors, GL_STATIC_DRAW);

	GLuint tvbo = 0;

	glGenBuffers(1, &tvbo);

	glBindBuffer(GL_ARRAY_BUFFER, tvbo);

	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), textCoords, GL_STATIC_DRAW);

	// create vertex array

	GLuint vao = 0;

	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);


	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, pvbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, cvbo);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, tvbo);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	// create shader

	std::shared_ptr<neu::Shader> vs = neu::g_resources.Get<neu::Shader>("shaders/basic.vert", GL_VERTEX_SHADER);
	
	std::shared_ptr<neu::Shader> fs = neu::g_resources.Get<neu::Shader>("shaders/basic.frag", GL_FRAGMENT_SHADER);

	// create program

	GLuint program = glCreateProgram();
	
	glAttachShader(program, fs->m_shader);
	
	glAttachShader(program, vs->m_shader);
	
	glLinkProgram(program);

	glUseProgram(program);

	GLint uniform1 = glGetUniformLocation(program, "scale");

	GLint uniform2 = glGetUniformLocation(program, "tint");

	GLint uniform3 = glGetUniformLocation(program, "transform");

	glm::mat4 mx{ 1 };

	//mx = glm::scale(glm::vec3{.7, .7, .7, .7});

	//create texture

	std::shared_ptr<neu::Texture> texture1 = neu::g_resources.Get<neu::Texture>("textures/box.png");

	std::shared_ptr<neu::Texture> texture2 = neu::g_resources.Get<neu::Texture>("textures/llama.png");

	texture1->Bind();

	bool quit = false;

	while (!quit){

		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyDown(neu::key_escape) == neu::InputSystem::State::Pressed) quit = true;
		
		glUniform3f(uniform2, 1, 0, 0);

		glUniform1f(uniform1, std::sin(neu::g_time.time * 4));

		mx = glm::eulerAngleXYZ(0.0f, 0.0f, neu::g_time.time * 7);

		glUniformMatrix4fv(uniform3, 1, GL_FALSE, glm::value_ptr(mx));
	
		neu::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		neu::g_renderer.EndFrame();
	
	}

	neu::Engine::Instance().Shutdown();

	return 0;

}
