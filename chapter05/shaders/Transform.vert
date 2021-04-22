#version 450

uniform mat4 uWorldTransform;
uniform mat4 uViewProjection;

in vec3 inPosition;

void main()
{
    vec4 position = vec4(inPosition, 1);
    gl_Position = position * uWorldTransform * uViewProjection;
}