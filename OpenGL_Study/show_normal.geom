#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;

in VS_OUT 
{
    vec3 normal;
} gs_in[];

const float MAGNITUDE = 0.02;

void GenerateLine(mat3 normalMatrix, int index)
{
    //gl_Position = gl_in[index].gl_Position;
    gl_Position = projection * view * model * gl_in[index].gl_Position;
    EmitVertex();
    //gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * MAGNITUDE;
    vec4 ptOnNormal = view * model * gl_in[index].gl_Position + vec4(normalize(normalMatrix * gs_in[index].normal) * MAGNITUDE, 0.0f);
    gl_Position = projection * ptOnNormal;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    mat3 nMat = mat3(transpose(inverse(view*model)));
    GenerateLine(nMat, 0); // 第一个顶点法线
    GenerateLine(nMat, 1); // 第二个顶点法线
    GenerateLine(nMat, 2); // 第三个顶点法线
}