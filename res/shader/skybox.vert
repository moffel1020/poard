#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 texCoord;

uniform mat4 uProjection;
uniform mat4 uView;

void main() {
    vec4 pos = uProjection * uView * vec4(aPos, 1.0);
    texCoord = aPos;

    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
}