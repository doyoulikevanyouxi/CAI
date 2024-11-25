#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec4 color;
out vec4 verColor;
out vec2 textCor;
uniform mat4 model;		//ģ�;���
uniform mat4 projection; //ͶӰ����

void main(){
	gl_Position = projection  * model * vec4(vertex,1.0f);
	verColor =  color;
}