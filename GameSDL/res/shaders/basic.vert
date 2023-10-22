#version 460 core

layout (location = 0) in vec4 aPos;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 transformation_matrix;

void main()
{
    gl_Position = projection_matrix * view_matrix * transformation_matrix * aPos;
}