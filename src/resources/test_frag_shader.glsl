#version 450 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D srcTexture;

void main()
{
    FragColor = texture(srcTexture, texCoord) * vec4(vertexColor.xyz, 1.0);
}