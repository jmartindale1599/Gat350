#version 430 core 

layout(location = 0) in vec3 vposition; // 0

layout(location = 1) in vec2 vtextcoord;

layout(location = 2) in vec3 vnormal;

out vec3 color;

out vec2 textcoord;

struct Light{

	vec3 color;

	vec3 ambient;

	vec4 position;

};

struct Material{

	vec3 color;

	float shinnyness;

};

uniform Light light;

uniform Material material;

uniform mat4 model;

uniform mat4 view;

uniform mat4 projection;

void main(){

	textcoord = vtextcoord;

	vec3 ambient = light.ambient * material.color;

	//DIFFUSE

	//create model view matrix

	mat4 modelView = view * model;

	//transform normals to view space

	vec3 normal = mat3(modelView) * vnormal;

	//transform positions to view space

	vec4 position = modelView * vec4(vposition, 1);

	//calculate light direction (unit vector)

	vec3 lightDir = normalize(vec3(light.position * material.shinnyness - position));

	//calculate light intensity with dit product (normal * light direction)

	float intensity = max(dot(lightDir, normal), 0);

	vec3 diffuse = light.color * intensity;

	//SPECULAR

	vec3 specular = vec3(0);

	if(intensity > 0){

		vec3 reflection = reflect(-lightDir, normal);

		vec3 viewDir = normalize(-vec3(position));

		intensity = max(dot(reflection, viewDir), 0);

		intensity = pow(intensity, 32.0);

		specular = light.color * intensity;

	}

	color = vec3(0.2) + diffuse + specular;

	mat4 mvp = projection * view * model;

	gl_Position = mvp * vec4(vposition, 1.0);

}
