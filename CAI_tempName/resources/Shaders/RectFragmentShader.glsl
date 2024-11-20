#version 330 core
out vec4 fragColor;
in vec4 verColor;
in vec2 textCor;
uniform sampler2D sampl;
uniform mat4 projection_color; //ÑÕÉ«Í¶Ó°¾ØÕó
void main(){
    vec4 vertColor = projection_color * verColor;
	if(textCor.x < 0 || textCor.y <0){
		if(vertColor.w <0.1)
			discard;
		fragColor = vertColor;
	}else{
		vec4 tColor = texture(sampl,textCor);
		if(tColor.a<0.1)
			fragColor = vertColor;
		else
			fragColor = tColor;
	}
}