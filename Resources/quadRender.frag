#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D tex;
uniform float currentTime;

void main(){
	color = texture( tex, UV).xyz; //+ 0.005*vec2( sin(currentTime+1024.0*UV.x),cos(currentTime+768.0*UV.y)) ).xyz ;
}
