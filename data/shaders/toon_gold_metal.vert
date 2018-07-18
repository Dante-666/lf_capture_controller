#version 130

varying vec3 Normal;
varying vec3 Vertex; 
varying vec3 LightPos;

void main(void)
{
	Normal = normalize(gl_NormalMatrix * gl_Normal);
	LightPos = vec3(gl_LightSource[0].position);
    Vertex = vec3(gl_ModelViewMatrix * gl_Vertex);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
