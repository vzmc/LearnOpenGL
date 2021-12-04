#version 330 core
in GS_OUT 
{
    vec3 color;
} fs_out;

out vec4 FragColor;

void main()
{
    FragColor = vec4(fs_out.color, 1.0);
}