#version 430 core 

layout(location = 0) in vec3 vposition; // 0

//layout(location = 1) in vec3 vcolor; // 1

layout(location = 1) in vec2 vtextcoord;

out vec3 color;

out vec2 textcoord;

uniform float scale;

uniform mat4 mvp;

void main(){

	//color = vcolor;

	textcoord = vtextcoord;

	vec4 tposition = mvp * vec4(vposition * scale, 1.0);

	gl_Position = tposition; //vec4(vposition * scale, 1.0);

}
