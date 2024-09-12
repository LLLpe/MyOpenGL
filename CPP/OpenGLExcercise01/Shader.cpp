#include "Shader.h"
#include <iostream>
#include <fstream>//获取File需要用到
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


//using namespace std;
//声明Shader()方法
//C++中，这代表执行在Shader作用域下的Shader方法
Shader::Shader(const char* vertexPath , const char* fragmentPath)
{
	//std命名空间下的ifstream类型
	//FileBuffer
	std::ifstream  vertexFile;
	std::ifstream  fragmentFile;
	//StringBuffer是用来解释和归类FileBuffer的
	std::stringstream vertexSStream;
	std::stringstream fragmentSStream;
	

	//开档
	//并不意味着已经将文件读取出来了，而是告知程序要读取
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	//读档测试。测试是否坏档
	vertexFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

	//检测
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw std::exception("open file error");
		}

		//顺序：Disk => FileBuffer => StringBuffer => String => CharString
		
		//真正开始读档=>rdbuf()
		//Disk=>FileBuffer=>StringBuffer
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		//把StringBuffer的内容转为String类，存起来 
		vertexString = vertexSStream.str();//toString()
		fragmentString = fragmentSStream.str();

		//String => CharString
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		//将着色器代码编译为二进制Code
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		checkCompileErrors(vertexShader, "VERTEX");

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		checkCompileErrors(fragmentShader, "FRAGMENT");

		//声明ShaderProgram，并且将二进制Code Attach到ShaderProgram上，变为可执行程序
		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);//定位函数地址，拼接成完整的ShaderProgram
		checkCompileErrors(ID, "PROGRAM");

		//生成ShaderProgram之后就可以删除掉shader了
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		//printf(vertexSource);
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}
}
	int i = 0;
void Shader::use() {
	glUseProgram(ID);
	if(i == 00)
	{
		printf(vertexSource);
		printf(fragmentSource);
		i++;
	}
}
void Shader::checkCompileErrors(unsigned int ID, std::string type)
{
	int success;
	char infoLog[512];
	if (type != "PROGRAM")
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			cout << "Shader compile error:" << infoLog << endl;
		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout << "program compile error:" << infoLog << endl;
		}
	}
}

