#version 330 core
#define NR_POINT_LIGHTS 9
#define NR_SPOT_LIGHTS 0

struct Material {
    sampler2D diffuse1;
    sampler2D specular1;
    sampler2D reflection1;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform bool directionalLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform int numPointLights;
uniform Material material;
uniform samplerCube skybox;

// Function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
    // Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // == ======================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == ======================================
    vec3 result = vec3(0);
    // Phase 1: Directional lighting
    if (directionalLight)
    {
        result = CalcDirLight(dirLight, norm, viewDir);
    }
    // // Phase 2: Point lights
    for (int i = 0; i < numPointLights; i++)
    {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    }
    if (numPointLights > 0)
    {
        result /= numPointLights;
    }
    // Phase 3: Spot light
    // result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    // Calculate reflections/refractions
    // float reflect_intensity = texture(material.reflection1, TexCoords).r;
    // vec3 I = normalize(FragPos - viewPos);
    // vec3 R = reflect(I, normalize(Normal));
    // vec3 R = refract(I, normalize(Normal), ratio);
    // vec4 reflect_color;
    // if (reflect_intensity > 0.1)
    //    reflect_color = texture(skybox, R) * reflect_intensity;
    color = vec4(result, 1.0f); // + reflect_color; //vec4(result, 1.0f);
}

// Calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    // Combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular1, TexCoords));
    return (ambient + diffuse + specular);
}

// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // Combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular1, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}