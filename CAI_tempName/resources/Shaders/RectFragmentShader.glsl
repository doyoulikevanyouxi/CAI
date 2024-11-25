#version 330 core
out vec4 fragColor;
in vec4 verColor;
in vec2 textCor;
uniform mat4 projection_color; //ÑÕÉ«Í¶Ó°¾ØÕó
void main(){
    fragColor = projection_color * verColor;
}