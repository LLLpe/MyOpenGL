#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h" //�ڲ�������<>�������ĵ������Է����еĸ��Ӱ���Ŀ¼���ҵ���,�Զ������""

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//��ѧ���
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <sstream>std::stringstream ss;
#include "Camera.h"





//float vertices[] = {
//    // positions          // colors           // texture coords
//     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
//};
 
//float vertices[] = {
//	// positions         // colors
//	 -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // bottom right
//	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,// bottom left
//	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.5f, 1.0f// top 
//
//};

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = {
	// ע��������0��ʼ! 
	// ��������ʱ�뷽��д

	0, 2, 1, // ��һ��������
	2, 0, 3  // �ڶ���������

};
 

//unsigned int indices[] = 
//{  
//	// note that we start from 0!
//	0, 1, 2,   // first triangle
//};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};


//const char* vertexshaderSource =
//"#version 330 core                                        \n "
//"layout (location = 0) in vec3 aPos;                      \n "
//"layout (location = 1) in vec3 aColor;                    \n "
//"out vec4 vertexColor;                                    \n "
//"void main(){                                             \n "
//"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);         \n "
////"vertexColor = vec4(1.0f,0.5f,0.2f,1.0);      \n "
//"vertexColor = vec4(aColor.x,aColor.y,aColor.z,1.0); }     \n ";
//
//const char* fragshaderSource =
//"#version 330 core                                 \n "
//"out vec4 FragColor;                               \n "
//"in vec4 vertexColor;                              \n "
//"void main(){                                      \n "
//"    FragColor = vertexColor;}                     \n ";

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

////camera
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
//float pitch = 0.0f;
//float fov = 45.0f;

bool firstMouse = true;
float lastX = 4000 / 2.0;
float lastY = 2000 / 2.0;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));

int main(){

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//Open GLFW Window
	 //����˴�����ֱ����GLFWwindow window�Ļ� ����û�취��window��ָ��(point)ȥ�����飬������GLFWwindow* window
	//glfwCreateWindow()�����Ƿ���һ��Pointָ��
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "My OpenGL Game", NULL, NULL);
	if (window == NULL)
	{
		printf("Open Window False");
		glfwTerminate(); //glfw��ֹ��
		return -1;          //���� -1 ��ָ�������˳�
	}
	//MakeContex����˼������ʹ�ø�window
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) //�жϿ����Ƿ�ɹ�
	{
		printf("Init GLEW Failed");
		glfwTerminate();
		return -1;
	}

	//������
	glViewport(0, 0, 1920, 1080);
	
	Shader* myshader = new Shader("vertexSource.txt" ,"fragmentSource.txt");

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//unsigned int instanceVBO;
	//glGenBuffers(1, &instanceVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 10, &cubePositions[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);


	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	////������ɫ������
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexshaderSource, NULL);
	//glCompileShader(vertexShader);

	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragshaderSource, NULL);
	//glCompileShader(fragmentShader);

	//����ɫ���������ӵ���ɫ������Shader Program Object��
	//Ϊ���ܣ���������ʱ�򼤻���ɫ������Ȼ�󱻵��ã������Ƹ�shaderʲôʱ�򱻵��ã�
	//unsigned int shaderprogram;
	//shaderprogram = glCreateProgram();
	//glAttachShader(shaderprogram, vertexShader);
	//glAttachShader(shaderprogram, fragmentShader);
	//glLinkProgram(shaderprogram);

	//����������ȡ��VBO=>VAO.ARRAY_BUFFER���Ĺ���
	//���Unity�е�TEXCOORD0 TEXCOORD1 TEXCOORD2
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE ,5 * sizeof(float), (void*)0);//����index0,��3��ֵ��ÿ��5������һ�Σ���ʼ��ƫ��0��ֵ
	glEnableVertexAttribArray(0);//����

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	//����index1,��3��ֵ��ÿ��6������һ�Σ���ʼ��ƫ��3��ֵ
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));	//����index1,��2��ֵ��ÿ��5������һ�Σ���ʼ��ƫ��63��ֵ
	glEnableVertexAttribArray(2);

	//����һ��Ĭ����ͼ��Bind��VAO�Ľӿ��ϣ�׼������
	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	//�ж���ͼ�Ļ����ͻ���Ҫʹ��glActiveTexture()������Ϊ������ͼ������ͼ�Ĳ�λ������GPU������������ͼ
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);

	//�������ݽṹ��ʹ��stbi��ͼ
	int	width, height, nrChannel;

	//ͼƬ��ʽ�У�Y��0�������Ϸ���������OpenGLֱ�Ӷ�ͼ�������ͼƬ�����Ϸ���ʼ��ͼ��
	// ����OpenGL����ʾͼƬʱ���Ǵ����½ǿ�ʼ��ʾ��(�����ĵ�һ�����ػᱻ��ʾ�����·���)������Ч�����еߵ���
	//��ˣ�������һ��flip�Ĳ���
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

	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TexBufferB);
	unsigned char* data2 = stbi_load("pic2.jpg", &width, &height, &nrChannel, 0);
	if (data2)
	{
		//��VAO��д����
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "load image falied." << endl;
	}

	stbi_image_free(data2);

	//�������
	//Camera camera(glm::vec3(0, -1.0f, 5.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));


	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 modeMatrix = glm::mat4(1.0f);
	modeMatrix = glm::rotate(modeMatrix , glm::radians( -0.0f ), glm::vec3(1.0f, 1.0f, 0));
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	//viewMatrix = glm::translate(viewMatrix, glm::vec3(0, 0,-3.0f));
	//viewMatrix = camera.GetViewMatrix();

	glm::mat4 projMatrix = glm::mat4(1.0f);
	//����Ž�ֵ����߱ȣ�����ƽ��
	projMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	

	while (!glfwWindowShouldClose(window))  //������رմ��ڣ��Ǿ�һֱִ��SwapBuffer��˫�ػ���
	{
		//trans = glm::rotate(trans, glm::radians(5.0f), glm::vec3(0.0, 0.0, 0.5));
		//trans = glm::scale(trans, glm::vec3(1.01, 1.01, 1.01));
		//Input
		processInput(window); //һ���Ȼ�ȡ���룬����һ��ѭ����ʱ����ִ��������ز���������д��glfwPollEvents()ǰ��

		//rendering command here
		// ���õ�ɫ
		//Ҳ���ڲ���֮ǰ�������Ƿ�ɹ�
		glClearColor(0.3f, 0.3f, 0.5f, 1.0f);//�����ú���Ҫ����Ļ�����ô��ɫ
		//ִ������(����ִֻ��ColorBuffer������)�����⻹��GL_DEPTH_BUFFER_BIT��GL_DEPTH_STENCIL_BIT(��ȣ�ģ��)
		//������һ֡��Z����
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBufferA);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TexBufferB); 

		//VAO������ʹ��glDrawArrays�Ĳ��� Vertices Array?
		glBindVertexArray(VAO);
		//EBO������ʹ��glDrawElements�Ĳ���
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		viewMatrix = camera.GetViewMatrix();

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 modeMatrix2 = glm::mat4(1.0f);//��ʼ��
			modeMatrix2 = glm::translate(modeMatrix2, cubePositions[i]);

			glUseProgram(myshader->ID);
			myshader->use();
			glUniform1i(glGetUniformLocation(myshader->ID, "ourTexture"), 0);//��"ourTexture"����GL_TEXTURE0
			glUniform1i(glGetUniformLocation(myshader->ID, "ourTexture2"), 1);//��"ourTexture"����GL_TEXTURE1
			//��transformLoc����Vert�е� "transform"
			unsigned int transformLoc = glGetUniformLocation(myshader->ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			
			//for (unsigned int i = 0; i < 10; i++)
			//{
			//	stringstream ss ;
			//	string index;
			//	ss << i;
			//	index = ss.str();
			//	myshader.setVec3(("offsets[" + index + "]").c_str(), cubePositions[i]);
			//	unsigned int offsetLoc = glGetUniformLocation(myshader->ID, "offset");
			//	glUniform3fv(offsetLoc,1, 1.0f);
			//}

			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "modeMatrix"), 1, GL_FALSE, glm::value_ptr(modeMatrix2));
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "projMatrix"), 1, GL_FALSE, glm::value_ptr(projMatrix));

			//ÿ����һ��Draw����������һ��draw call��
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//glBindVertexArray(VAO);
			//glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		}

		//check and call event swap the buffer
		//Double buffer�����ָֻʾ��������Ļ����һ��Buffer�����ڼ����buffer��Ҫʱ�䣬���ټ��ϻ����ڼ�����׺���Ѷ���ţ�����Buffer���Ƶļ���ڼ������˸��
		//�����frontBuffer�� backBuffer����Ⱦָ�������backBuffer�ϣ�Ȼ��backBuffer��"Swap"��frontBuffer��,��������ڼ�Ͳ������
		glfwSwapBuffers(window);

		glfwPollEvents();  //��ȡ���̸���������
		camera.UpdateCameraPos();
	}

	//����رմ���ʱִ��
	//���ڳ���ֹͣʱ����̨ҲҪ�ص�glfw
	glfwTerminate(); 
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		//glfwWindowShouldClose(window);
	}
	float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		//cameraPos += cameraSpeed * cameraFront;
		camera.speedZ = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		//cameraPos -= cameraSpeed * cameraFront;
		camera.speedZ = -1.0f;
	}
	else {
		camera.speedZ = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.speedR = -1.0f;
		//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		camera.speedR = 1.0f;
	}
	else{
		camera.speedR = 0.0f;
	}
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xoffset = xPos - lastX;
	float yoffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;
	//printf(" % f \n", xoffset);

	camera.ProcessMouseMovement(xoffset, yoffset);

}