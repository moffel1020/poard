
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;

void main()
{
    fragPos = vec3(uModel * vec4(aPos, 1.0));
    gl_Position = uProjection * uView * vec4(fragPos, 1.0);
    normal = aNormal;
    texCoord = aTexCoord;
}