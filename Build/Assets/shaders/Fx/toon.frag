#version 430 core

#define POINT  0 

#define DIRECTIONAL 1 

#define SPOTLIGHT 2 

in vec3 position;

in vec3 normal;

in vec2 textcoord;

out vec4 fcolor; // pixel to draw

struct Light{

	int type; 

	vec3 ambient;

	vec3 color;

	vec4 position;

	vec3 direction; 
	
	float cutoff; 

	float exponent; 

};

struct Material{

	vec3 color;

	float shininess;

	vec2 uv_tiling;

	vec2 uv_offset;

};

uniform Light light;

uniform Material material;

uniform vec3 tint;

const int levels = 13;

const float scaleFactor = 1.0/levels;

void toon(vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular){

	// direction vector to light

	// calculate light direction (unit vector)

	vec3 light_dir = (light.type == DIRECTIONAL) ? normalize(-light.direction) : normalize(vec3(light.position) - position);
 
	// if spotlight, compute intensity based on angle to cutoff

	float spot_intensity = 1;

	if (light.type == SPOTLIGHT){

		// get cosine of light direction and direction vector from light
	
	float cosine = dot(light.direction, -light_dir);
	
	// get angle
	
	float angle = acos(cosine);
 
	
	// if inside of cutoff, set spot intensity
	
	spot_intensity = (angle < light.cutoff) ? pow(cosine, light.exponent) : 0;
	
	}
 
	// AMBIENT
	
	ambient = light.ambient * material.color;
 
	// DIFFUSE
	
	float intensity = max(dot(light_dir, normal), 0) * spot_intensity;
	
	intensity = floor(intensity * levels) * scaleFactor;



	// calculate diffuse color
	
	diffuse = light.color * material.color * intensity;
 
	// SPECULAR
	
	specular = vec3(0);
	
//	if (intensity > 0){

//		// calculate reflection vector 
	
//	// light direction reflected around normal vector [ \|/ ]
	
//	vec3 reflection = reflect(-light_dir, normal);
	
//	// create direction vector from eye (origin) to vertex position
	
//	vec3 view_dir = normalize(-vec3(position));
	
//	// calculate light intensity with dot production (reflection * view direction)
	
//	intensity = max(dot(reflection, view_dir), 0);

//	intensity = pow(intensity, material.shininess);
	
//	// calculate specular color
	
//	specular = light.color * material.color * intensity;
	
//	}

}

void main(){

	vec3 ambient;

	vec3 diffuse;

	vec3 specular;
 
	toon(position, normal, ambient, diffuse, specular);
 
	vec2 ttexcoord = (textcoord * material.uv_tiling) + material.uv_offset;
 
	fcolor = vec4(ambient + diffuse, 1) + vec4(specular, 1);

}
