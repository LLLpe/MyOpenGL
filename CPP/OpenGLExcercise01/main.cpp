#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h" //�ڲ�������<>�������ĵ������Է����еĸ��Ӱ���Ŀ¼���ҵ���,�Զ������""

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		//glfwWindowShouldClose(window);
	}
}

//float vertices[] = {
//	// positions          // colors           // texture coords
//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
//};
 
float vertices[] = {
	// positions         // colors
	 -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // bottom right
	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,// bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.5f, 1.0f// top 

};


//unsigned int indices[] = {
//	// ע��������0��ʼ! 
//	// ��������ʱ�뷽��д
//
//	0, 1, 2, // ��һ��������
//	2, 3, 0  // �ڶ���������
//
//};
 

unsigned int indices[] = 
{  
	// note that we start from 0!
	0, 1, 2,   // first triangle
};


const char* vertexshaderSource =
"#version 330 core                                        \n "
"layout (location = 0) in vec3 aPos;                      \n "
"layout (location = 1) in vec3 aColor;                    \n "
"out vec4 vertexColor;                                    \n "
"void main(){                                             \n "
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);         \n "
//"vertexColor = vec4(1.0f,0.5f,0.2f,1.0);      \n "
"vertexColor = vec4(aColor.x,aColor.y,aColor.z,1.0); }     \n ";

const char* fragshaderSource =
"#version 330 core                                 \n "
"out vec4 FragColor;                               \n "
"in vec4 vertexColor;                              \n "
"void main(){                                      \n "
"    FragColor = vertexColor;}                     \n ";


int main(){


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//Open GLFW Window
	 //����˴�����ֱ����GLFWwindow window�Ļ� ����û�취��window��ָ��(point)ȥ�����飬������GLFWwindow* window
	//glfwCreateWindow()�����Ƿ���һ��Pointָ��
	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
	if (window == NULL)
	{
		printf("Open Window False");
		glfwTerminate(); //glfw��ֹ��
		return -1;          //���� -1 ��ָ�������˳�
	}
	//MakeContex����˼������ʹ�ø�window
	glfwMakeContextCurrent(window);

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) //�жϿ����Ƿ�ɹ�
	{
		printf("Init GLEW Failed");
		glfwTerminate();
		return -1;
	}

	//������
	glViewport(0, 0, 800, 600);
	
	Shader* myshader = new Shader("vertexSource.txt" ,"fragmentSource.txt");

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//VBO��Vertex Buffer Objects������CPU�����ģ����Ϣ��һ����String����
	//VAO��VertexArraysObject ������VBO�е���Ϣ��һ����˵һ��ģ�ͣ�����һ��VAO��������
	//����VAO��ģ�Ͷ��㣬UV��������Ϣ�����ˣ���ô�Ϳ��Է��㵥��ѡ�񶥵�Ϊ����VertexShader������
	//VAO���Գ�������Buffer��ArrayBuffer��ElementBuffer��������ʹ��ArrayBuffer��
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); //��VAO����ID
	glBindVertexArray(VAO); //��VAO������VAO����Ҫ����Ķ���
	//printf("%d", VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);//��VBO����ID
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//��VBO������VBO���ӵ�VAO��ArrayBuffer�ӿ�

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	////������ɫ������
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexshaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragshaderSource, NULL);
	glCompileShader(fragmentShader);

	//����ɫ���������ӵ���ɫ������Shader Program Object��
	//Ϊ���ܣ���������ʱ�򼤻���ɫ������Ȼ�󱻵��ã������Ƹ�shaderʲôʱ�򱻵��ã�
	unsigned int shaderprogram;
	shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, vertexShader);
	glAttachShader(shaderprogram, fragmentShader);
	glLinkProgram(shaderprogram);

	//����������ȡ��VBO=>VAO.ARRAY_BUFFER���Ĺ���
	//���Unity�е�TEXCOORD0 TEXCOORD1 TEXCOORD2
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE ,8 * sizeof(float), (void*)0);//����index0,��3��ֵ��ÿ��6������һ�Σ���ʼ��ƫ��0��ֵ
	glEnableVertexAttribArray(0);//����

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	//����index1,��3��ֵ��ÿ��6������һ�Σ���ʼ��ƫ��3��ֵ
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));	//����index1,��2��ֵ��ÿ��6������һ�Σ���ʼ��ƫ��6��ֵ
	glEnableVertexAttribArray(2);

	//����һ��Ĭ����ͼ��Bind��VAO�Ľӿ��ϣ�׼������
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);

	//�������ݽṹ��ʹ��stbi��ͼ
	int	width, height, nrChannel;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load("pic.jpg", &width, &height, &nrChannel, 0);
	//������ݴ���
	if (data)
	{
		//��VAO��д����
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "load image falied." << endl;
	}
	stbi_image_free(data);


	while (!glfwWindowShouldClose(window))  //������رմ��ڣ��Ǿ�һֱִ��SwapBuffer��˫�ػ���
	{
		//Input
		processInput(window); //һ���Ȼ�ȡ���룬����һ��ѭ����ʱ����ִ��������ز���������д��glfwPollEvents()ǰ��

		//rendering command here
		// ���õ�ɫ
		//Ҳ���ڲ���֮ǰ�������Ƿ�ɹ�
		glClearColor(0.3f, 0.3f, 0.5f, 1.0f);//�����ú���Ҫ����Ļ�����ô��ɫ
		glClear(GL_COLOR_BUFFER_BIT); //ִ������(����ִֻ��ColorBuffer������)�����⻹��GL_DEPTH_BUFFER_BIT��GL_DEPTH_STENCIL_BIT(��ȣ�ģ��)
		glBindTexture(GL_TEXTURE_2D, TexBuffer);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glUseProgram(shaderprogram);
		glUseProgram(myshader->ID);
		myshader->use();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//check and call event swap the buffer
		//Double buffer�����ָֻʾ��������Ļ����һ��Buffer�����ڼ����buffer��Ҫʱ�䣬���ټ��ϻ����ڼ�����׺���Ѷ���ţ�����Buffer���Ƶļ���ڼ������˸��
		//�����frontBuffer�� backBuffer����Ⱦָ�������backBuffer�ϣ�Ȼ��backBuffer��"Swap"��frontBuffer��,��������ڼ�Ͳ������
		glfwSwapBuffers(window);

		glfwPollEvents();  //��ȡ���̸���������
	}

	//����رմ���ʱִ��
	//���ڳ���ֹͣʱ����̨ҲҪ�ص�glfw
	glfwTerminate(); 
	return 0;
}

