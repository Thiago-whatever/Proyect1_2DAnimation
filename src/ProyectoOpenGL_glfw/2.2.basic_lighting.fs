#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 lightPos2;
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // ambient
    float ambientStrength = 0.1;//ka
    vec3 ambient = ambientStrength * lightColor; //ka*Ia
  	
    // diffuse 
    vec3 norm = normalize(Normal);//vector normal- N
    vec3 lightDir = normalize(lightPos - FragPos);//vector de direccion- L
    float diff = max(dot(norm, lightDir), 0.0);//prodpunto(L y N)
    vec3 diffuse = diff * lightColor;//prodpunto(L y N) * I
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);//N
    vec3 reflectDir = reflect(-lightDir, norm);  //V era el angulo reflejadi con respecto a la normal
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);//ese 32 es el ns
    vec3 specular = specularStrength * spec * lightColor;  //specularStrength es ks (factor de atenuación)
    
    

    //segunda luz
    //difusa
    vec3 lightDir2 = normalize(lightPos2 - FragPos); // Direction vector for second light
    float diff2 = max(dot(norm, lightDir2), 0.0); // Dot product for diffuse lighting
    vec3 diffuse2 = diff2 * lightColor; // Diffuse component for second light
    //especular
    vec3 reflectDir2 = reflect(-lightDir2, norm);  // Reflection direction for second light
    float spec2 = pow(max(dot(viewDir, reflectDir2), 0.0), 32); // Specular component
    vec3 specular2 = specularStrength * spec2 * lightColor;  // Specular for second light

    // Combine the lighting contributions of both lights
    vec3 result = (ambient + diffuse + diffuse2 + specular + specular2) * objectColor;

    //vec3 result = (ambient + diffuse + specular) * objectColor;//objectColor es el color del pixel
    FragColor = vec4(result, 1.0);
} 