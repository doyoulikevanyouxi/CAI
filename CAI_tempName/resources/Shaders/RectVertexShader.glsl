#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec4 color;
out vec4 verColor;
out vec2 textCor;
uniform mat4 model;		//模型矩阵
uniform mat4 projection; //投影矩阵

void main(){
	gl_Position = projection  * model * vec4(vertex,1.0f);
	verColor =  color;
}