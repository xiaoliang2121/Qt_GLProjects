#version 330

//layout (location = 0)
//layout (location = 1)
in vec3 aPos;
in vec3 aColor;
out vec3 ourColor;

void main(void)
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
}
