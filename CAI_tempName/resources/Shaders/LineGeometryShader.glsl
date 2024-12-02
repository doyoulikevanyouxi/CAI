#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;


in VS_OUT{
	vec4 rectColor;
	vec2 rectSize;
	vec2 pt1;
	vec2 pt2;
	float lthickness;
}gs_in[];

out vec2 center;
out vec2 size;
out vec4 color;
out vec2 startPoint;
out vec2 endPoint;
out float line_thickness;

void main(){
	size = gs_in[0].rectSize;
	center = gl_in[0].gl_Position.xy+vec2(size.x,-size.y)*0.5;
	color = gs_in[0].rectColor;
	startPoint = gs_in[0].pt1;
	endPoint = gs_in[0].pt2;
	line_thickness = gs_in[0].lthickness;
	//左上
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
	//右上
	gl_Position = vec4(gl_in[0].gl_Position.x+size.x,gl_in[0].gl_Position.yzw);
	EmitVertex();
	//左下
	gl_Position = vec4(gl_in[0].gl_Position.x,gl_in[0].gl_Position.y-size.y,gl_in[0].gl_Position.zw);
	EmitVertex();
	//右下
	gl_Position = vec4(gl_in[0].gl_Position.x+size.x,gl_in[0].gl_Position.y-size.y,gl_in[0].gl_Position.zw);
	EmitVertex();
	EndPrimitive();
}