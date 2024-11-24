#version 330 core
out vec4 fragColor;
in vec4 verColor;
uniform sampler2D sampl;
uniform mat4 projection_color; //ÑÕÉ«Í¶Ó°¾ØÕó
void main(){
    fragColor = projection_color * verColor;
}
