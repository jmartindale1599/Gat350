#version 430 core 

layout(location = 0) in vec3 vposition; // 0

layout(location = 1) in vec3 vcolor; // 1

out vec3 color;

uniform float scale;

uniform mat4 transform;

void main(){

	color = vcolor;

	vec4 tposition = vec4(vposition * scale, 1.0) * transform;

	gl_Position = tposition; //vec4(vposition * scale, 1.0);

}
