#include "Shader.h"
#include <iostream>
#include <fstream>//��ȡFile��Ҫ�õ�
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


//using namespace std;
//����Shader()����
//C++�У������ִ����Shader�������µ�Shader����
Shader::Shader(const char* vertexPath , const char* fragmentPath)
{
	//std�����ռ��µ�ifstream����
	//FileBuffer
	std::ifstream  vertexFile;
	std::ifstream  fragmentFile;
	//StringBuffer���������ͺ͹���FileBuffer��
	std::stringstream vertexSStream;
	std::stringstream fragmentSStream;
	

	//����
	//������ζ���Ѿ����ļ���ȡ�����ˣ����Ǹ�֪����Ҫ��ȡ
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	//�������ԡ������Ƿ񻵵�
	vertexFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

	//���
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw std::exception("open file error");
		}

		//˳��Disk => FileBuffer => StringBuffer => String => CharString
		
		//������ʼ����=>rdbuf()
		//Disk=>FileBuffer=>StringBuffer
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		//��StringBuffer������תΪString�࣬������ 
		vertexString = vertexSStream.str();//toString()
		fragmentString = fragmentSStream.str();

		//String => CharString
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		//����ɫ���������Ϊ������Code
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

		//����ShaderProgram�����ҽ�������Code Attach��ShaderProgram�ϣ���Ϊ��ִ�г���
		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);//��λ������ַ��ƴ�ӳ�������ShaderProgram
		checkCompileErrors(ID, "PROGRAM");

		//����ShaderProgram֮��Ϳ���ɾ����shader��
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

