#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT
{
    vec4 normal;
    vec3 position;
    vec2 texCoords;
} gs_in[];

out VS_OUT 
{
    vec4 normal;
    vec3 position;
    vec2 texCoords;
} gs_out;

uniform float time;

vec4 explode(vec4 position, vec3 normal, float y)
{
    float magnitude = 0.5f;
    float value = sin(time + y * 3.1415926);

    if(value < 0)
    {
        value = 0;
    }

    normal = normalize(normal);

    vec3 direction = normal * value * magnitude; 
    return position + vec4(direction, 0.0f);
}

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main() {    
    vec3 normal = GetNormal();

    gl_Position = explode(gl_in[0].gl_Position, normal, gs_in[0].position.y);
    gs_out.normal =  gs_in[0].normal;
    gs_out.position = gs_in[0].position;
    gs_out.texCoords = gs_in[0].texCoords;
    EmitVertex();
    
    gl_Position = explode(gl_in[1].gl_Position, normal, gs_in[1].position.y);
    gs_out.normal =  gs_in[1].normal;
    gs_out.position = gs_in[1].position;
    gs_out.texCoords = gs_in[1].texCoords;
    EmitVertex();
    
    gl_Position = explode(gl_in[2].gl_Position, normal, gs_in[2].position.y);
    gs_out.normal =  gs_in[2].normal;
    gs_out.position = gs_in[2].position;
    gs_out.texCoords = gs_in[2].texCoords;
    EmitVertex();

    EndPrimitive();
}