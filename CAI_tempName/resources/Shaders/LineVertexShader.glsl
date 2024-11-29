#version 330 core
layout(location = 0) in vec3 point;
layout(location = 1) in vec4 point_color;

uniform mat4 model;		//模型矩阵
uniform mat4 projection; //投影矩阵
out VS_OUT {
	vec4 pcolor;
}pt;

void main(){
	gl_Position = projection  * model * vec4(point,1.0f);
	pt.pcolor = point_color;
}