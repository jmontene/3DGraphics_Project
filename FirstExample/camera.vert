#version 430 core
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexture;

out vec2 texCoord;
smooth out vec3 fragPos;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main(){
	texCoord = vTexture;
	fragPos = vPosition;
	gl_Position = Projection * View * Model * vec4(vPosition, 1.0f);
}
