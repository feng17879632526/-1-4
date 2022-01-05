//
//#include <fstream>
//#include "glad/glad.h"
//#include "GLFW/glfw3.h"
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include<iostream>
//#include<vector>
//#include<math.h>
//using namespace std;
//// 窗口尺寸宏定义
//#define WINDOW_WIDTH 800
//#define WINDOW_HEIGHT 600
//
//
//
//// 顶点着色器代码
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
//// 片元着色器代码
//const char* FSSOURCE =
//"#version 330\n"
//"in vec3 color;\n"
//"\n"
//"void main()\n"
//"{\n"
//"	gl_FragColor = vec4(color, 1);\n"
//"}";
//
//// 几个全局变量
//unsigned int MyShaderProgram;
//unsigned int PVBO, CVBO, VAO, EBO;
//glm::mat4 mMat, vMat, pMat;
//
//// 模型数据
//int num; //记录输入的点的个数
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
//	// 生成顶点着色器
//	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &VSSOURCE, NULL);
//	glCompileShader(vertexShader);
//
//	// 生成片元着色器
//	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &FSSOURCE, NULL);
//	glCompileShader(fragmentShader);
//
//	// 链接着色器形成小程序
//	MyShaderProgram = glCreateProgram();
//	glAttachShader(MyShaderProgram, vertexShader);
//	glAttachShader(MyShaderProgram, fragmentShader);
//	glLinkProgram(MyShaderProgram);
//
//	// 链接完毕后着色器可删除
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//}
//
//void bind_data()
//{
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &PVBO); // PVBO 存坐标
//	glGenBuffers(1, &CVBO); // CVBO 存颜色
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//
//	// 将内存中的顶点坐标数据传输到显存的 PVBO 中
//	glBindBuffer(GL_ARRAY_BUFFER, PVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * VNB, MyPoints, GL_STATIC_DRAW);
//
//	// 给顶点着色器中location为0的位置绑定数据
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	// 将内存中的顶点颜色数据传输到显存的 CVBO 中
//	glBindBuffer(GL_ARRAY_BUFFER, CVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * VNB, MyColors, GL_STATIC_DRAW);
//
//	// 给顶点着色器中location为1的位置绑定数据
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//
//	// 将内存中的三角形连接数据传输到显存的 EBO 中
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3 * FNB, MyIndices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//}
//
//void display()
//{
//	// 将帧缓存颜色重置为默认颜色
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glUseProgram(MyShaderProgram);
//	glBindVertexArray(VAO);
//	// 画三角形
//	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	//// 画线
//	glDrawArrays(GL_LINE_STRIP, 0, num);
//	glDrawArrays(GL_LINE_STRIP, num, VNB-num);
//	//glDrawArrays(GL_LINE_STRIP, 0, VNB);
//}
//
//void process_input(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}
//
//
//class Point {
//public:
//	float x;
//	float y;
//	Point(float x, float y) {
//		this->x = x;
//		this->y = y;
//	}
//	Point() {
//
//	}
//};
////-----------------------deCasteljau----------------------------
//Point approximate(double t, Point const& pt1, Point const& pt2)
//{
//	double x = pt1.x * (1 - t) + pt2.x * t;
//	double y = pt1.y * (1 - t) + pt2.y * t;
//
//	return Point(x, y);
//}
//
//Point deCasteljau(vector<Point> const& points,float t)
//{
//		vector<Point> temp1 = points;
//		while (temp1.size() > 1)
//		{
//			vector<Point> temp2;
//
//			for (int i = 0; i < temp1.size() - 1; i++)
//			{
//				Point pt1 = temp1[i];
//				Point pt2 = temp1[i + 1];
//
//				temp2.push_back(approximate(t, pt1, pt2));
//			}
//
//			temp1 = temp2;
//		}
//		cout << "(" << temp1[0].x << ", " << temp1[0].y << ")" << endl;
//	return temp1[0];
//}
////-----------------------------------------------------------------------
//
////-------------------------Bernstein多项式-------------------------------
////阶乘
//int Factorial(int n)
//{
//	if (n == 0) return 1;
//	int result = n;
//	for (n--; n > 0; n--)
//		result *= n;
//	return result;
//}
////组合数
//int CombinatorialNum(int i, int n)
//{
//	if (i > n) return 0;
//	return Factorial(n) / (Factorial(i) * Factorial(n - i));
//}
////伯恩斯坦多项式方法求曲线上一点
////伯恩斯坦多项式
//float BernsteinNum(int i, int n, float t)
//{
//	return CombinatorialNum(i, n) * pow(t, i) * pow(1.0f - t, n - i);
//}
//
//Point bernstein(vector<Point> const& points, float t)
//{
//	int n = points.size() - 1;// n 阶是 n+1 个顶点
//	Point point(0,0);
//	for (int i=0; i <= n; i++) {
//		point.x += BernsteinNum(i, (int)n, t) * points[i].x;
//		point.y += BernsteinNum(i, (int)n, t) * points[i].y;
//		cout << "(" << points[i].x << ", " << points[i].y << ")" << endl;
//	}
//	return point;
//}
//
//
//
//
////-----------------------------------------------------------------------
//vector<Point> getPoints(vector<Point> const& points,float precision, Point (*algorithm)(vector<Point> const&, float)) {
//	vector<Point> bezierPoints;
//	for (double t = 0; t < 1; t = t + precision)
//	{
//		bezierPoints.push_back((*algorithm)(points, t));
//	}
//	return bezierPoints;
//}
//
//void addToMyPoints(vector<Point> points,float color1,float color2,float color3) {
//	int k = VNB*3;
//	for (int i = 0; i < points.size(); i++) {
//			MyPoints[k] = points[i].x;
//			MyColors[k++] = color1;
//			MyPoints[k] = points[i].y;
//			MyColors[k++] = color2;
//			MyPoints[k] = 0;
//			MyColors[k++] = color3;
//			VNB++;
//	}
//}
//
//
//int main(void)
//{
//	int op;
//	vector<Point> points;
//	float precision,x,y;
//	cout << "1. de Casteljau" << endl;
//	cout << "2. Bernstein" << endl;
//	cout << "Please input your choice:" << endl;
//	cin >> op;
//	//op = 1;
//	cout << "Please input your precision:" << endl;
//	cin >> precision;
//	//precision = 0.01;
//	cout << "Please input your number of points:" << endl;
//	cin >> num;
//	//num = 3;
//	cout << "Please input your points:" << endl;
//	for (int i = 0; i < num; i++) {
//		cin >> x;
//		cin >> y;
//		Point p(x, y);
//		points.push_back(p);
//	}
//	//points.push_back(Point(1, 80));
//	//points.push_back(Point(50, 34));
//	//points.push_back(Point(100, 90));
//	cout << "The resulting points are shown below:" << endl;
//	if (op == 1) {
//		//先绘制输入点所构成的折线
//		addToMyPoints(points, 0.0, 1.0, 0.0);
//		addToMyPoints(getPoints(points, precision, deCasteljau),1.0,0.0,0.0);
//	}
//	else if (op == 2) {
//		addToMyPoints(points, 0.0, 1.0, 0.0);
//		addToMyPoints(getPoints(points, precision, bernstein), 1.0, 0.0, 0.0);
//	}
//	else {
//		cout << "error choice" << endl;
//	}
//
//
//
//	// 初始化 GLFW
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 不支持固定管线
//
//	// 创建窗口
//	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, u8"张小锋8002119102", NULL, NULL);
//	if (window == NULL)
//	{
//		glfwTerminate();
//		return -1;
//	}
//
//	// 将窗口映射到OpenGL帧缓存
//	glfwMakeContextCurrent(window);
//
//	// 注册窗口大小改变时的回调函数为 resize_window
//	glfwSetFramebufferSizeCallback(window, resize_window);
//
//	// 初始化GLAD
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		glfwTerminate();
//		return -1;
//	}
//
//	// 生成着色器程序
//	init_shaders();
//
//	// 绑定数据
//	bind_data();
//
//	// 设置帧缓存的默认颜色（即窗口的背景颜色）
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//	// 设置顶点的大小为10像素宽
//	glPointSize(10.0f);
//
//	// 开启深度测试
//	//glEnable(GL_DEPTH_TEST);
//
//	// 初始化模型、视图、投影矩阵
//	mMat = glm::mat4(1.0f);
//	vMat = glm::mat4(1.0f);
//	pMat = glm::mat4(1.0f);
//
//	vMat = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
//	float ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
//	//pMat = glm::perspective(glm::radians(60.0f), ratio, 0.1f, 100.0f);
//	pMat = glm::ortho(0.0f, ratio*100, 0.0f, 100.0f, 0.0f, 100.0f);  //改为正交投影方便观察，并修改投影矩阵，使得纵坐标0到100的点落在窗口中(横坐标0~133.3)
//
//	glUseProgram(MyShaderProgram);
//	glUniformMatrix4fv(glGetUniformLocation(MyShaderProgram, "mMat"), 1, GL_FALSE, &mMat[0][0]);
//	glUniformMatrix4fv(glGetUniformLocation(MyShaderProgram, "vMat"), 1, GL_FALSE, &vMat[0][0]);
//	glUniformMatrix4fv(glGetUniformLocation(MyShaderProgram, "pMat"), 1, GL_FALSE, &pMat[0][0]);
//
//	// 进入循环
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
