#version 330 core
//��X��Ϊ����
layout (location = 0) in vec3 vertex;	//��������
layout (location = 1) in vec2 size;		//���δ�С
layout (location = 2) in vec4 color;	//��ɫ
layout (location = 3) in vec4 conerRadius; //�߽ǰ뾶
layout (location = 4) in float borderSize;
layout (location = 5) in vec4 borderColor;

uniform vec2 iResolution;	//�ֱ���
uniform float colorResolution; //��ɫ�ֱ���
uniform mat4 model;	//ģ�;���
uniform mat4 projection; //ͶӰ����

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