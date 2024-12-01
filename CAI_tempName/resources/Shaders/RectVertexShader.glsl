#version 330 core
//以X作为参照
layout (location = 0) in vec3 vertex;	//顶点数据
layout (location = 1) in vec2 size;		//矩形大小
layout (location = 2) in vec4 color;	//颜色
layout (location = 3) in vec4 conerRadius; //边角半径
layout (location = 4) in float borderSize;
layout (location = 5) in vec4 borderColor;

uniform vec2 iResolution;	//分辨率
uniform float colorResolution; //颜色分辨率
uniform mat4 model;	//模型矩阵
uniform mat4 projection; //投影矩阵

out VS_OUT{
	vec4 rectColor;
	vec4 rectRadius;
	vec2 rectSize;
	float border_size;
	vec4 border_color;
}vs_out;
 
void main(){
	gl_Position = projection  * model * vec4(vertex,1.0f);
	vs_out.rectSize = size / iResolution*2.0;
	vs_out.rectColor = color / colorResolution;
	vs_out.rectRadius = conerRadius /iResolution.x*2.0;
	vs_out.border_size = borderSize / iResolution.x * 2.0;
	vs_out.border_color = borderColor / colorResolution;
}