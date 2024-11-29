#version 330 core
layout(location = 0) in vec3 point;
layout(location = 1) in vec4 point_color;

uniform mat4 model;		//ģ�;���
uniform mat4 projection; //ͶӰ����
out VS_OUT {
	vec4 pcolor;
}pt;

void main(){
	gl_Position = projection  * model * vec4(point,1.0f);
	pt.pcolor = point_color;
}