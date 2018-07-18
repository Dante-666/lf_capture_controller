#version 130

varying vec3 Normal;
varying vec3 Vertex;
varying vec3 LightPos;

vec3 UnlitColor = vec3(0.05, 0.05, 0.05);
vec3 OutlineColor = vec3(0.0, 0.0, 0.0);
vec3 DiffuseColor = vec3(0.56, 0.56, 0.56);
vec3 SpecularColor = vec3(0.3, 0.3, 0.3);

float UnlitOutlineThickness = 0.1;
float LitOutlineThickness = 0.2;

float DiffuseThreshold = 0.9;
float Shininess = 2;

void main (void)
{
    vec3 eyeVec = normalize(-Vertex);
    vec3 lightVec = normalize(LightPos);
    vec3 eyeLightVec = normalize(eyeVec+lightVec);

    vec3 fragmentColor = UnlitColor * DiffuseColor;
    
    if(max(0.0, dot(Normal, lightVec)) >= DiffuseThreshold) {
        fragmentColor = DiffuseColor;
    }

    if(dot(eyeVec, Normal) < 
       mix(UnlitOutlineThickness, 
           LitOutlineThickness, 
           max(0.0, dot(Normal, lightVec)))) {
        fragmentColor = OutlineColor;
    }
    
    vec3 specularReflection;
    if(dot(Normal, lightVec) > 0.1) {
        specularReflection = SpecularColor * pow(max(0.0, dot(reflect(-lightVec, Normal), eyeVec)), Shininess);
        fragmentColor = DiffuseColor + specularReflection;
    }

    gl_FragColor = vec4(fragmentColor, 1.0);

}
