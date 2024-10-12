#version 330 core                                

out vec4 FragColor;  

in vec4 vertexColor;  
in vec2 texCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main()
{   
	//FragColor = vertexColor;
	FragColor = texture(ourTexture,texCoord)* texture(ourTexture2,texCoord);
}      


//out vec4 FragColor;
//  
//uniform vec4 ourColor; // we set this variable in the OpenGL code.
//
//void main()
//{
//    //FragColor = ourColor;
//    FragColor = vec4(1,1,1,1);
//}   