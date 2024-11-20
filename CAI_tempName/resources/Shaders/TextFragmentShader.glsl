in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 textColor;
uniform mat4 projection_color; //ÑÕÉ«Í¶Ó°¾ØÕó
void main()
{   
    vec4 sampled =  vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    vec4 tColor = projection_color * textColor;
    color = tColor * sampled;
}
