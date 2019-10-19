#version 440

layout (location=0) in vec3 vertex_position;
layout (location=1) in vec3 vertex_color;
layout (location=2) in vec2 vertex_texcoord;

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcoord;

uniform mat4 modelMatrix;
uniform mat4  viewMatrix;
uniform mat4 projectionMatrix;

void main(){
	vs_position = vec4(modelMatrix * vec4(vertex_position, 1.f)).xyz; //World Coordinates
	vs_color = vertex_color;
	vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y*-1.f);

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_position, 1.f); // clip coordinates
}
