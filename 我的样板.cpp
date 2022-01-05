//
//#include <fstream>
//#include "glad/glad.h"
//#include "GLFW/glfw3.h"
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include<iostream>
//using namespace std;
//// ���ڳߴ�궨��
//#define WINDOW_WIDTH 800
//#define WINDOW_HEIGHT 600
//
//// ������ɫ������
//const char* VSSOURCE =
//"#version 330\n"
//"\n"
//"layout(location = 0) in vec3 iPos;\n"
//"layout(location = 1) in vec3 iColor;\n"
//"\n"
//"uniform mat4 mMat;\n"
//"uniform mat4 vMat;\n"
//"uniform mat4 pMat;\n"
//"\n"
//"out vec3 color;\n"
//"\n"
//"void main()\n"
//"{\n"
//"	gl_Position = pMat * vMat * mMat * vec4(iPos, 1);\n"
//"	color = iColor;\n"
//"}";
//
//// ƬԪ��ɫ������
//const char* FSSOURCE =
//"#version 330\n"
//"in vec3 color;\n"
//"\n"
//"void main()\n"
//"{\n"
//"	gl_FragColor = vec4(color, 1);\n"
//"}";
//
//// ����ȫ�ֱ���
//unsigned int MyShaderProgram;
//unsigned int PVBO, CVBO, VAO, EBO;
//glm::mat4 mMat, vMat, pMat;
//
//// ģ������
//int VNB = 0;
//float MyPoints[2000] = {
//	//-0.5f, -0.5f, 0.5f,  // bottom left
//	//0.5f, -0.5f, 0.0f,   // bottom right
//	//0.5f,  0.5f, -0.5f,   // top right
//	//-0.5f,  0.5f, 0.0f   // top left 
//};
//float MyColors[2000] = {
//	//1.0f,  0.0f, 0.0f,  // top right
//	//0.0f,  1.0f, 0.0f,  // bottom right
//	//0.0f,  0.0f, 1.0f,  // bottom left
//	//0.5f,  0.2f, 0.8f   // top left 
//};
//int FNB = 0;
//int MyIndices[2000] = {  // note that we start from 0!
//	//0, 1, 2,  // first Triangle
//	//1, 2, 3   // second Triangle
//};
//
//
//void resize_window(GLFWwindow* window, int w, int h)
//{
//	glViewport(0, 0, w, h);
//}
//
//void init_shaders()
//{
//	// ���ɶ�����ɫ��
//	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &VSSOURCE, NULL);
//	glCompileShader(vertexShader);
//
//	// ����ƬԪ��ɫ��
//	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &FSSOURCE, NULL);
//	glCompileShader(fragmentShader);
//
//	// ������ɫ���γ�С����
//	MyShaderProgram = glCreateProgram();
//	glAttachShader(MyShaderProgram, vertexShader);
//	glAttachShader(MyShaderProgram, fragmentShader);
//	glLinkProgram(MyShaderProgram);
//
//	// ������Ϻ���ɫ����ɾ��
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//}
//
//void bind_data()
//{
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &PVBO); // PVBO ������
//	glGenBuffers(1, &CVBO); // CVBO ����ɫ
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//
//	// ���ڴ��еĶ����������ݴ��䵽�Դ�� PVBO ��
//	glBindBuffer(GL_ARRAY_BUFFER, PVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * VNB, MyPoints, GL_STATIC_DRAW);
//
//	// ��������ɫ����locationΪ0��λ�ð�����
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	// ���ڴ��еĶ�����ɫ���ݴ��䵽�Դ�� CVBO ��
//	glBindBuffer(GL_ARRAY_BUFFER, CVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * VNB, MyColors, GL_STATIC_DRAW);
//
//	// ��������ɫ����locationΪ1��λ�ð�����
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//
//	// ���ڴ��е��������������ݴ��䵽�Դ�� EBO ��
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3 * FNB, MyIndices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//}
//
//void display()
//{
//	// ��֡������ɫ����ΪĬ����ɫ
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glUseProgram(MyShaderProgram);
//	glBindVertexArray(VAO);
//	// ��������
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	// ������
//	glDrawArrays(GL_POINTS, 0, VNB);
//}
//
//void process_input(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}
//
//int main(void)
//{
//
//
//	// ��ʼ�� GLFW
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ��֧�̶ֹ�����
//
//	// ��������
//	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, u8"��С��8002119102", NULL, NULL);
//	if (window == NULL)
//	{
//		glfwTerminate();
//		return -1;
//	}
//
//	// ������ӳ�䵽OpenGL֡����
//	glfwMakeContextCurrent(window);
//
//	// ע�ᴰ�ڴ�С�ı�ʱ�Ļص�����Ϊ resize_window
//	glfwSetFramebufferSizeCallback(window, resize_window);
//
//	// ��ʼ��GLAD
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		glfwTerminate();
//		return -1;
//	}
//
//	// ������ɫ������
//	init_shaders();
//
//	// ������
//	bind_data();
//
//	// ����֡�����Ĭ����ɫ�������ڵı�����ɫ��
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//	// ���ö���Ĵ�СΪ10���ؿ�
//	glPointSize(10.0f);
//
//	// ������Ȳ���
//	//glEnable(GL_DEPTH_TEST);
//
//	// ��ʼ��ģ�͡���ͼ��ͶӰ����
//	mMat = glm::mat4(1.0f);
//	vMat = glm::mat4(1.0f);
//	pMat = glm::mat4(1.0f);
//
//	vMat = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
//	float ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
//	//pMat = glm::perspective(glm::radians(60.0f), ratio, 0.1f, 100.0f);
//	pMat = glm::ortho(0.0f, ratio * 100, 0.0f, 100.0f, 0.0f, 100.0f);  //��Ϊ����ͶӰ����۲죬���޸�ͶӰ����ʹ��������0��100�ĵ����ڴ�����(������0~133.3)
//
//	glUseProgram(MyShaderProgram);
//	glUniformMatrix4fv(glGetUniformLocation(MyShaderProgram, "mMat"), 1, GL_FALSE, &mMat[0][0]);
//	glUniformMatrix4fv(glGetUniformLocation(MyShaderProgram, "vMat"), 1, GL_FALSE, &vMat[0][0]);
//	glUniformMatrix4fv(glGetUniformLocation(MyShaderProgram, "pMat"), 1, GL_FALSE, &pMat[0][0]);
//
//	// ����ѭ��
//	while (!glfwWindowShouldClose(window))
//	{
//		process_input(window);
//		display();
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}
//
