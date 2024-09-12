#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h" //内部引用用<>（可在文档的属性方案中的附加包含目录中找到）,自定义的用""

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
//	// 注意索引从0开始! 
//	// 按顶点逆时针方向写
//
//	0, 1, 2, // 第一个三角形
//	2, 3, 0  // 第二个三角形
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
	 //如果此处声明直接用GLFWwindow window的话 可能没办法用window的指针(point)去做事情，所以用GLFWwindow* window
	//glfwCreateWindow()本身是返回一个Point指针
	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
	if (window == NULL)
	{
		printf("Open Window False");
		glfwTerminate(); //glfw终止掉
		return -1;          //返回 -1 是指非正常退出
	}
	//MakeContex，意思接下来使用该window
	glfwMakeContextCurrent(window);

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) //判断开启是否成功
	{
		printf("Init GLEW Failed");
		glfwTerminate();
		return -1;
	}

	//开窗！
	glViewport(0, 0, 800, 600);
	
	Shader* myshader = new Shader("vertexSource.txt" ,"fragmentSource.txt");

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
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

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	////编译着色器代码
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexshaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragshaderSource, NULL);
	glCompileShader(fragmentShader);

	//将着色器代码链接到着色器程序（Shader Program Object）
	//为了能：激活对象的时候激活着色器程序，然后被调用，即控制该shader什么时候被调用！
	unsigned int shaderprogram;
	shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, vertexShader);
	glAttachShader(shaderprogram, fragmentShader);
	glLinkProgram(shaderprogram);

	//配置数据挖取（VBO=>VAO.ARRAY_BUFFER）的规则
	//类比Unity中的TEXCOORD0 TEXCOORD1 TEXCOORD2
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE ,8 * sizeof(float), (void*)0);//分配index0,挖3个值，每隔6个数挖一次，起始点偏移0个值
	glEnableVertexAttribArray(0);//激活

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	//分配index1,挖3个值，每隔6个数挖一次，起始点偏移3个值
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));	//分配index1,挖2个值，每隔6个数挖一次，起始点偏移6个值
	glEnableVertexAttribArray(2);

	//生成一张默认贴图，Bind到VAO的接口上，准备采样
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);

	//声明数据结构，使用stbi读图
	int	width, height, nrChannel;
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


	while (!glfwWindowShouldClose(window))  //如果不关闭窗口，那就一直执行SwapBuffer，双重缓冲
	{
		//Input
		processInput(window); //一般先获取输入，在下一次循环的时候再执行输入相关操作，所以写在glfwPollEvents()前面

		//rendering command here
		// 设置底色
		//也用于测试之前的配置是否成功
		glClearColor(0.3f, 0.3f, 0.5f, 1.0f);//先配置好我要将屏幕清成生么颜色
		glClear(GL_COLOR_BUFFER_BIT); //执行清理(这里只执行ColorBuffer的清理)，此外还有GL_DEPTH_BUFFER_BIT，GL_DEPTH_STENCIL_BIT(深度，模板)
		glBindTexture(GL_TEXTURE_2D, TexBuffer);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glUseProgram(shaderprogram);
		glUseProgram(myshader->ID);
		myshader->use();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//check and call event swap the buffer
		//Double buffer：如果只指示程序在屏幕绘制一个Buffer，由于计算该buffer需要时间，，再加上绘制期间很容易很杂讯干扰，所以Buffer绘制的间隔期间会有闪烁。
		//因此有frontBuffer和 backBuffer，渲染指令绘制在backBuffer上，然后backBuffer再"Swap"到frontBuffer上,这样间隔期间就不会出错
		glfwSwapBuffers(window);

		glfwPollEvents();  //获取键盘跟鼠标的输入
	}

	//点击关闭窗口时执行
	//窗口程序停止时，后台也要关掉glfw
	glfwTerminate(); 
	return 0;
}

