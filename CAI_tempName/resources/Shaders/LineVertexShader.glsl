#version 330 core
//��X��Ϊ����
layout (location = 0) in vec3 vertex;	//��������
layout (location = 1) in vec2 size;		//���δ�С
layout (location = 2) in vec4 color;	//��ɫ
layout (location = 3) in vec2 point1;  
layout (location = 4) in vec2 point2;  
layout (location = 5) in float thickness;


uniform vec2 iResolution;	//�ֱ���
uniform float colorResolution; //��ɫ�ֱ���
uniform mat4 model;	//ģ�;���
uniform mat4 projection; //ͶӰ����

out VS_OUT{
	vec4 rectColor;
	vec2 rectSize;
	vec2 pt1;
	vec2 pt2;
	float lthickness;
}vs_out;


void main(){
	gl_Position = projection  * model * vec4(vertex,1.0f);
	vs_out.rectSize = size / iResolution*2.0;
	vs_out.rectColor = color / colorResolution;
	vs_out.pt1 =  (projection  * model *vec4(point1,1.0f,1.0f)).xy;
	vs_out.pt2 =  (projection  * model *vec4(point2,1.0f,1.0f)).xy;
	vs_out.lthickness = thickness / iResolution.x * 2.0;
}