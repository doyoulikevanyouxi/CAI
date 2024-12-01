#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;


in VS_OUT{
	vec4 rectColor;
	vec4 rectRadius;
	vec2 rectSize;
}gs_in[];


uniform vec2 iResolution;	//分辨率
uniform float colorResolution; //颜色分辨率

out vec2 center;
out vec2 size;
out vec4 color;
out float radius;
void main(){
	size = gs_in[0].rectSize;
	center = gl_in[0].gl_Position.xy+vec2(size.x,-size.y)*0.5;
	color = gs_in[0].rectColor;
	//左上
	radius = gs_in[0].rectRadius.x;
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
	//右上
	//radius = gs_in[0].rectRadius.y;
	radius = gs_in[0].rectRadius.y;

	gl_Position = vec4(gl_in[0].gl_Position.x+size.x,gl_in[0].gl_Position.yzw);
	EmitVertex();
	//左下
	//radius = gs_in[0].rectRadius.z;
	gl_Position = vec4(gl_in[0].gl_Position.x,gl_in[0].gl_Position.y-size.y,gl_in[0].gl_Position.zw);
	EmitVertex();
	//右下
	//radius = gs_in[0].rectRadius.w;
	gl_Position = vec4(gl_in[0].gl_Position.x+size.x,gl_in[0].gl_Position.y-size.y,gl_in[0].gl_Position.zw);
	EmitVertex();
	EndPrimitive();
}