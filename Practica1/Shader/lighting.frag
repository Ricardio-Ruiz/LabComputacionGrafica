#version 330 core
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform Light light2;       //Segunda fuente de luz

uniform sampler2D texture_diffusse;       //para aplicar tambien a la textura

void main()
{
    // LUZ 1 ==========================================
    // Ambient
    vec3 ambient = light.ambient *material.diffuse;
    
    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);    //segun la drieccion de la luz
    float diff = max(dot(norm, lightDir), 0.0);             //atenuación 
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);             //componente de reflexion 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);   //intensidad del brillo 
    vec3 specular = light.specular * (spec * material.specular);

    // LUZ 2 ==========================================
    // Ambient 2
    vec3 ambient2 = light2.ambient * material.diffuse;
    
    // Diffuse 2
    vec3 lightDir2 = normalize(light2.position - FragPos);
    float diff2 = max(dot(norm, lightDir2), 0.0);
    vec3 diffuse2 = light2.diffuse * diff2 * material.diffuse;
    
    // Specular 2
    //vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir2 = reflect(-lightDir2, norm);
    float spec2 = pow(max(dot(viewDir, reflectDir2), 0.0), material.shininess);
    vec3 specular2 = light2.specular * (spec2 * material.specular);

    
    //vec3 result = ambient + diffuse + specular;         //suma de cada componente de iluminación
      vec3 result = (ambient + diffuse + specular) + (ambient2 + diffuse2 + specular2); //agregando la luz2
    color = vec4(result, 1.0f) * texture(texture_diffusse, TexCoords);  //aplicacion 
}