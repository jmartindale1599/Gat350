#version 430 core 
  
in vec2 texcoord; 
  
out vec4 fcolor; 

const float THICC = .9;

uniform sampler2D textureMap; 
  
void main(){ 

 //ONLINE SCANLINE effect

    vec3 color = texture(textureMap, texcoord).rgb;
    
    fcolor = vec4(color,1);

} 
