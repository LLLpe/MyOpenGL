#version 330 core                                       
layout (location = 0) in vec3 aPos;                     
layout (location = 1) in vec3 aColor;                   
layout (location = 2) in vec2 aTexCoord; 

out vec4 vertexColor;     
out vec2 texCoord;
//uniform mat4 transform;
uniform mat4 modeMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main()
{                                 
	vertexColor = vec4(aColor ,1.0);     
	gl_Position = projMatrix * viewMatrix * modeMatrix * vec4(aPos , 1.0);
	//gl_Position = transform * vec4(aPos + offset , 1.0);
	texCoord = aTexCoord;
}