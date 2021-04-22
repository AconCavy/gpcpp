#version 450

uniform mat4 uWorldTransform;
uniform mat4 uViewProjection;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

out vec2 fragTexCoord;

void main()
{
    vec4 position = vec4(inPosition, 1);
    gl_Position = position * uWorldTransform * uViewProjection;
    fragTexCoord = inTexCoord;
}