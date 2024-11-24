#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 size;
layout (location = 2) in vec4 color;	//��������


uniform mat4 model;		//ģ�;���
uniform mat4 projection; //ͶӰ����

out VS_OUT{
	vec2 proSize;
	vec4 vColor;
}vs_out;

void main(){ 
	gl_Position = vec4(0.5,0.5,0,1.0f);
	gl_Position =projection * model * vec4(vertex,1.0f);
	vs_out.proSize =  (projection*vec4(size,0,0)).xy;
	vs_out.vColor =  color;
}
