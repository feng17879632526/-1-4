//#pragma execution_character_set("utf-8")
//#include <fstream>
//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include<iostream>
//#include<algorithm>
//#include<math.h>
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
//
//// ģ������
//int VNB = 0;
//float MyPoints[50000] = {}; //�����������һ����
//float MyColors[50000] = {};
////int FNB = 2;
////int MyIndices[] = {  // note that we start from 0!
////	0, 1, 2,  // first Triangle
////	0, 2, 3   // second Triangle
////};
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
//
//void bind_data()
//{
//
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
//	//// ���ڴ��е��������������ݴ��䵽�Դ�� EBO ��
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3 * FNB, MyIndices, GL_STATIC_DRAW);
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
//	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	// ������
//	glDrawArrays(GL_POINTS, 0, VNB);
//
//
//}
//
//void process_input(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}
//
////DDA�㷨
//void DDA(int x1, int y1, int x2, int y2) {
//	if (x1 > x2) {
//		swap(x1, x2);
//		swap(y1, y2);
//	}
//	double y = y1;
//	int k = 0;
//	float a = (float)(y2 - y1) / (x2 - x1); 
//	int t = 0;
//	for (int i = x1; i <= x2; i++) {
//		y += a;
//		VNB++;
//		MyPoints[k] = (float)i / 100;
//		MyColors[k] = 0.5f;
//		MyPoints[k + 1] = (float)round(y) / 100;
//		MyColors[k + 1] = 0.5f;
//		MyPoints[k+2] = 0;
//		MyColors[k + 2] = 0.5f;
//		k += 3;
//	}
//}
//
//
////bersenham�㷨
//void bersenham(int x1, int y1, int x2, int y2) {
//	if (x1 > x2) {
//		swap(x1, x2);
//		swap(y1, y2);
//	}
//	float h = 0;
//	int y = y1,k=0;
//	float a = (float)(y2 - y1) / (x2 - x1);//б��
//	for (int i = x1; i <= x2; i++) {
//		VNB++;
//		MyPoints[k] = (float)i / 100;
//		MyColors[k] = 0.5f;
//		MyPoints[k + 1] = y / 100.0;
//		MyColors[k + 1] = 0.5f;
//		MyPoints[k + 2] = 0;
//		MyColors[k + 2] = 0.5f;
//		k += 3;
//		h += abs(a);
//		if (h >= 1) h--;
//		if (h >= 0.5) {
//			if (a > 0) y++;
//			else y--;
//		}
//	}
//}
//
//
////  �ɸ�����������������꣬���������������
//double  triangleArea(int x1, int x2, int x3, int y1, int y2, int y3) {
//	return abs((x1 * y2 + x2 * y3 + x3 * y1- x2 * y1 - x3 * y2 - x1 * y3) / 2.0);
//}
////���������PAB��PAC��PBC�����֮����������ABC�������ȣ������ж���P��������ABC��(��������������)��
////  �жϵ�pos�Ƿ���ָ�����������ڡ�
//bool  isInner(int x1, int x2, int x3, int y1, int y2, int y3, int i, int j) {
//	double  sumArea = triangleArea(x1, x2, x3, y1, y2, y3);
//	double  area = triangleArea(i, x2, x3, j, y2, y3);
//	area += triangleArea(x1, i, x3, y1, j, y3);
//	area += triangleArea(x1, x2, i, y1, y2, j);
//	double  epsilon = 0.0001;   //  ���ڸ������ļ������������ָ��һ���㹻С�����������ж���������Ƿ�(����)��ȡ�
//	if (abs(sumArea - area) < epsilon) {
//		return   true;
//	}
//	return   false;
//}
//
//void rasterizedTriangle(int x1, int x2, int x3, int y1, int y2, int y3) {
//	int xmin = min(x1, min(x2, x3));
//	int xmax = max(x1, max(x2, x3));
//	int ymin = min(y1, min(y2, y3));
//	int ymax = max(y1, max(y2, y3));
//	int k = 0;
//	//�����Χ����ÿ�����Ƿ����������ڲ�������Ⱦ
//	for (int i = xmin; i <= xmax; i++) {
//		for (int j = ymin; j <= ymax; j++) {
//			if (isInner(x1, x2, x3, y1, y2, y3, i, j)) {
//				VNB++;
//				MyPoints[k] = (float)i / 100;
//				MyColors[k] = 0.5f;  
//				MyPoints[k+1] = (float)j / 100;
//				MyColors[k + 1] = 0.5f;  
//				MyPoints[k+2] = 0;
//				MyColors[k+2] = 0.5f;  
//				k += 3;
//			}
//		}
//	}
//}
//
//int main(void)
//{
//	//����������
//	int x1, y1, x2, y2, x3, y3;
//	cout << "1.DDA" << endl;
//	cout << "2.bersenham" << endl;
//	cout << "3.Rasterized triangle" << endl;
//	cout << "Please input your choice:" << endl;;
//	int op;
//	cin >> op;
//	cout << "please input points:";
//	switch (op) {
//	case 1:
//		cin >> x1 >> y1 >> x2 >> y2;
//		DDA(x1, y1, x2, y2);
//		break;
//	case 2:
//		cin >> x1 >> y1 >> x2 >> y2;
//		bersenham(x1, y1, x2, y2);
//		break;
//	case 3:
//		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
//		rasterizedTriangle(x1, x2, x3, y1, y2, y3);
//		break;
//	}
//	// ��ʼ�� GLFW
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ��֧�̶ֹ�����
//
//	// ��������
//	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "��С��8002119102", NULL, NULL);
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
//
//
//	// ������
//	bind_data();
//
//	// ����֡�����Ĭ����ɫ�������ڵı�����ɫ��
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//	// ���ö���Ĵ�СΪ4���ؿ�
//	glPointSize(4.0f);
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
//	pMat = glm::perspective(glm::radians(60.0f), ratio, 0.1f, 100.0f);
//	//pMat = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 0.1f, 100.0f);
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
