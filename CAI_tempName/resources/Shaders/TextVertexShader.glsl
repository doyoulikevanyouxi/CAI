#version 330 core
layout (location = 0) in vec3 vertexcoord; 
layout (location = 1) in vec2 textureC; 
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 model;

void main()
{
    gl_Position = projection * model * vec4(vertexcoord, 1.0f);
    TexCoords = textureC;
}