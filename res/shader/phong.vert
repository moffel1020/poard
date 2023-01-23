#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 normal;
out vec3 fragPos;

void main()
{
    normal = aNormal;
    fragPos = vec3(uModel * vec4(aPos, 1.0));

    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}