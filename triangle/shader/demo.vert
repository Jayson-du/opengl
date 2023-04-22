#version 430 core
layout (location = 0)
in vec3 aPos;
out float data;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    float value = 1024;
    int exp;
    data = frexp(value, exp);

    float result = data - 0.50;
    if (result < 0.000001) {
        data = 0.5f;
    } else {
        data = 1.0f;
    }
}