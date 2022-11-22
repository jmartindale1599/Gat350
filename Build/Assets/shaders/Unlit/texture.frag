#version 430 core

in vec2 texcoord;

out vec4 fcolor;

uniform sampler2D diffuseMap;

void main(){

	vec3 color = texture(diffuseMap, texcoord).rbg;

	float avg = (color.r + color.g + color.b);

	fcolor = vec4(vec3(0.5, avg, 0.5),1);

	//fcolor = texture(diffuseMap, texcoord);

}
