#version 330

out vec4 color;

in vec2 texCoord;

uniform sampler2D u_texture_side;

void main()
{
	color = texture(u_texture_side,texCoord);
}

