#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h" //内部引用用<>（可在文档的属性方案中的附加包含目录中找到）,自定义的用""

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//数学相关
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"


#pragma region Model Data
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
#pragma endregion

#pragma region Camera Declare
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region Input Declare
bool firstMouse = true;
float lastX = 4000 / 2.0;
float lastY = 2000 / 2.0;

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		//glfwWindowShouldClose(window);
	}
	//float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//cameraPos += cameraSpeed * cameraFront;
		camera.speedZ = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
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
	else {
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


#pragma endregion



int main(){
#pragma region Open Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//Open GLFW Window
	 //如果此处声明直接用GLFWwindow window的话 可能没办法用window的指针(point)去做事情，所以用GLFWwindow* window
	//glfwCreateWindow()本身是返回一个Point指针
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "My OpenGL Game", NULL, NULL);
	if (window == NULL)
	{
		printf("Open Window False");
		glfwTerminate(); //glfw终止掉
		return -1;          //返回 -1 是指非正常退出
	}
	//MakeContex，意思接下来使用该window
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) //判断开启是否成功
	{
		printf("Init GLEW Failed");
		glfwTerminate();
		return -1;
	}
	//开窗！
	glViewport(0, 0, 1920, 1080);
	
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
#pragma endregion 

	Shader* myshader = new Shader("vertexSource.vert" ,"fragmentSource.frag");

#pragma region Init and Load Models to VAO,VBO
	//VBO：Vertex Buffer Objects，缓存CPU传入的模型信息（一长串String）；
	//VAO：VertexArraysObject ，解析VBO中的信息，一般来说一个模型，就用一个VAO来缓存它
	//有了VAO后，模型顶点，UV，法线信息明了了，我么就可以方便单独选择顶点为传入VertexShader的数据
	//VAO可以持有两种Buffer，ArrayBuffer和ElementBuffer，这里先使用ArrayBuffer；
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); //给VAO配置ID
	glBindVertexArray(VAO); //绑定VAO：将该VAO设置要计算的对象
	//printf("%d", VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);//给VBO配置ID
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定VBO：将该VBO连接到VAO的ArrayBuffer接口
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//配置数据挖取（VBO=>VAO.ARRAY_BUFFER）的规则
	//类比Unity中的TEXCOORD0 TEXCOORD1 TEXCOORD2
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE ,5 * sizeof(float), (void*)0);//分配index0,挖3个值，每隔5个数挖一次，起始点偏移0个值
	glEnableVertexAttribArray(0);//激活

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	//分配index1,挖3个值，每隔6个数挖一次，起始点偏移3个值
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));	//分配index1,挖2个值，每隔5个数挖一次，起始点偏移63个值
	glEnableVertexAttribArray(2);
#pragma endregion

	//生成一张默认贴图，Bind到VAO的接口上，准备采样
	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	//有多张图的话，就还需要使用glActiveTexture()方法来为多张贴图安排贴图的槽位，否则GPU读不到其他贴图
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);

	//声明数据结构，使用stbi读图
	int	width, height, nrChannel;

	//图片格式中，Y轴0是在左上方，所以让OpenGL直接读图，他会从图片的左上方开始读图，
	// 但是OpenGL在显示图片时，是从左下角开始显示的(读到的第一个像素会被显示在左下方！)，所以效果会有颠倒！
	//因此，必须有一个flip的操作
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load("pic.jpg", &width, &height, &nrChannel, 0);
	//如果数据存在
	if (data)
	{
		//往VAO里写数据
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
		//往VAO里写数据
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "load image falied." << endl;
	}

	stbi_image_free(data2);

	//创建相机
	//Camera camera(glm::vec3(0, -1.0f, 5.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));


	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 modeMatrix = glm::mat4(1.0f);
	modeMatrix = glm::rotate(modeMatrix , glm::radians( -0.0f ), glm::vec3(1.0f, 1.0f, 0));
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	//viewMatrix = glm::translate(viewMatrix, glm::vec3(0, 0,-3.0f));
	//viewMatrix = camera.GetViewMatrix();

	glm::mat4 projMatrix = glm::mat4(1.0f);
	//相机张角值，宽高比，裁切平面
	projMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	

	while (!glfwWindowShouldClose(window))  //如果不关闭窗口，那就一直执行SwapBuffer，双重缓冲
	{
		//trans = glm::rotate(trans, glm::radians(5.0f), glm::vec3(0.0, 0.0, 0.5));
		//trans = glm::scale(trans, glm::vec3(1.01, 1.01, 1.01));
		//Input
		processInput(window); //一般先获取输入，在下一次循环的时候再执行输入相关操作，所以写在glfwPollEvents()前面

		//rendering command here
		// 设置底色
		//也用于测试之前的配置是否成功
		glClearColor(0.3f, 0.3f, 0.5f, 1.0f);//先配置好我要将屏幕清成生么颜色
		//执行清理(这里只执行ColorBuffer的清理)，此外还有GL_DEPTH_BUFFER_BIT，GL_DEPTH_STENCIL_BIT(深度，模板)
		//清理上一帧的Z缓冲
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBufferA);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TexBufferB); 

		//VAO：用于使用glDrawArrays的参数 Vertices Array?
		glBindVertexArray(VAO);

		viewMatrix = camera.GetViewMatrix();

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 modeMatrix2 = glm::mat4(1.0f);//初始化
			modeMatrix2 = glm::translate(modeMatrix2, cubePositions[i]);

			glUseProgram(myshader->ID);
			myshader->use();
			glUniform1i(glGetUniformLocation(myshader->ID, "ourTexture"), 0);//将"ourTexture"传入GL_TEXTURE0
			glUniform1i(glGetUniformLocation(myshader->ID, "ourTexture2"), 1);//将"ourTexture"传入GL_TEXTURE1
			//将transformLoc传入Vert中的 "transform"
			unsigned int transformLoc = glGetUniformLocation(myshader->ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "modeMatrix"), 1, GL_FALSE, glm::value_ptr(modeMatrix2));
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "projMatrix"), 1, GL_FALSE, glm::value_ptr(projMatrix));

			//每调用一次Draw函数，就是一次draw call！
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//check and call event swap the buffer
		//Double buffer：如果只指示程序在屏幕绘制一个Buffer，由于计算该buffer需要时间，，再加上绘制期间很容易很杂讯干扰，所以Buffer绘制的间隔期间会有闪烁。
		//因此有frontBuffer和 backBuffer，渲染指令绘制在backBuffer上，然后backBuffer再"Swap"到frontBuffer上,这样间隔期间就不会出错
		glfwSwapBuffers(window);
		glfwPollEvents();  //获取键盘跟鼠标的输入
		camera.UpdateCameraPos();
	}

	//点击关闭窗口时执行
	//窗口程序停止时，后台也要关掉glfw
	glfwTerminate(); 
	return 0;
}

