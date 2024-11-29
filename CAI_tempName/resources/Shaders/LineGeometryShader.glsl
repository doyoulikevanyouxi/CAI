#version 330 core
layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT {
	vec4  pcolor;
}gs_in[];

out vec4 vertexColor;

void main(){
	vec3 pt1 = gl_in[0].gl_Position.xyz;
	vec3 pt2 = gl_in[1].gl_Position.xyz;
	vertexColor = gs_in[1].pcolor;
	gl_Position = vec4(pt1,1.0);
	EmitVertex();
	gl_Position = vec4(pt2.x,pt1.y,pt1.z,1.0);
	EmitVertex();
	gl_Position = vec4(pt1.x,pt2.y,pt1.z,1.0);
	EmitVertex();
	vertexColor = gs_in[1].pcolor;
	gl_Position = vec4(pt2,1.0);
	EmitVertex();
	EndPrimitive();
}