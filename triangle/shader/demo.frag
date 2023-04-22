#version 430 core
in float data;
out vec4 FragColor;
void main()
{
    FragColor = vec4(data, 0.3f, 0.1f, 0.5f);
}