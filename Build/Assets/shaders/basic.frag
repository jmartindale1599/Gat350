#version 430 core

in vec3 color;

in vec2 textcoord;

out vec4 fcolor;

uniform vec3 tint;

uniform sampler2D textureSampler;

void main(){

	//fcolor = vec4(color * tint, 1.0);

	fcolor = texture(textureSampler, textcoord);

}
