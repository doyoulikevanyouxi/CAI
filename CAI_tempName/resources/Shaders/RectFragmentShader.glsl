#version 330 core
out vec4 fragColor;
in vec4 verColor;
uniform sampler2D sampl;
uniform mat4 projection_color; //��ɫͶӰ����
void main(){
    fragColor = projection_color * verColor;
}
