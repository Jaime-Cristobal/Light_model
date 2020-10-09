#version 330 core

struct Material 
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};


struct DirLight 
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;
uniform Material material;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform vec3 viewPos;
uniform vec3 texture_normal1;
uniform vec3 texture_height1;

in vec2 TexCoords;
in vec3 FragPos;

out vec4 FragColor;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{    
    // properties
    vec3 norm = normalize(texture_normal1);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Directional lighting
    vec3 result = CalcDirLight(dirLight, texture_normal1, viewDir);
    FragColor = vec4(result, 1.0);

    // FOR TESTING PURPOSES
    //vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
    //vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    //vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));
    //FragColor = texture(tex, TexCoords);
}


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // combine results
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));

    return (ambient + diffuse + specular);
}