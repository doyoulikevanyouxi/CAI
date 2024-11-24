#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;
in VS_OUT{
	 vec2 proSize;
	 vec4 vColor;
}gs_in[];
out vec4 verColor;
void main(){
	verColor = gs_in[0].vColor;
	gl_Position =  gl_in[0].gl_Position;
	EmitVertex();
	gl_Position =  gl_in[0].gl_Position + vec4(gs_in[0].proSize.x,0,0,0);
	EmitVertex();
	gl_Position =  gl_in[0].gl_Position + vec4(0,gs_in[0].proSize.y,0,0);
	EmitVertex();
	gl_Position =  gl_in[0].gl_Position + vec4(gs_in[0].proSize.x,gs_in[0].proSize.y,0,0);
	EmitVertex();
	EndPrimitive();
}