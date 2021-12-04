#version 330 core
out vec4 FragColor;

in VS_OUT
{
    vec4 normal;
    vec3 position;
    vec2 texCoords;
} fs_in;

uniform vec3 cameraPos;
uniform samplerCube skybox;

uniform sampler2D texture_diffuse1;

void main()
{          
//    float ratio = 1.00 / 1.40;
//    vec3 I = normalize(fs_in.position - cameraPos);
//    vec3 R = refract(I, normalize(fs_in.normal), ratio);
//    FragColor = vec4(texture(skybox, R).rgb, 1.0);

    FragColor = texture(texture_diffuse1, fs_in.texCoords);
}
