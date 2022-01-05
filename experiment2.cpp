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
//// 窗口尺寸宏定义
//#define WINDOW_WIDTH 800
//#define WINDOW_HEIGHT 600
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
//
//// 模型数据
//int VNB = 0;
//float MyPoints[50000] = {}; //三个坐标决定一个点
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
//
//void bind_data()
//{
//
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
//	//// 将内存中的三角形连接数据传输到显存的 EBO 中
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3 * FNB, MyIndices, GL_STATIC_DRAW);
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
//	// 画顶点
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
////DDA算法
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
////bersenham算法
//void bersenham(int x1, int y1, int x2, int y2) {
//	if (x1 > x2) {
//		swap(x1, x2);
//		swap(y1, y2);
//	}
//	float h = 0;
//	int y = y1,k=0;
//	float a = (float)(y2 - y1) / (x2 - x1);//斜率
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
////  由给定的三个顶点的坐标，计算三角形面积。
//double  triangleArea(int x1, int x2, int x3, int y1, int y2, int y3) {
//	return abs((x1 * y2 + x2 * y3 + x3 * y1- x2 * y1 - x3 * y2 - x1 * y3) / 2.0);
//}
////如果三角形PAB，PAC和PBC的面积之和与三角形ABC的面积相等，即可判定点P在三角形ABC内(包括在三条边上)。
////  判断点pos是否在指定的三角形内。
//bool  isInner(int x1, int x2, int x3, int y1, int y2, int y3, int i, int j) {
//	double  sumArea = triangleArea(x1, x2, x3, y1, y2, y3);
//	double  area = triangleArea(i, x2, x3, j, y2, y3);
//	area += triangleArea(x1, i, x3, y1, j, y3);
//	area += triangleArea(x1, x2, i, y1, y2, j);
//	double  epsilon = 0.0001;   //  由于浮点数的计算存在着误差，故指定一个足够小的数，用于判定两个面积是否(近似)相等。
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
//	//计算包围盒中每个点是否在三角形内并进行渲染
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
//	//输入点的坐标
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
//	// 初始化 GLFW
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 不支持固定管线
//
//	// 创建窗口
//	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "张小锋8002119102", NULL, NULL);
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
//
//
//	// 绑定数据
//	bind_data();
//
//	// 设置帧缓存的默认颜色（即窗口的背景颜色）
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//	// 设置顶点的大小为4像素宽
//	glPointSize(4.0f);
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
//	pMat = glm::perspective(glm::radians(60.0f), ratio, 0.1f, 100.0f);
//	//pMat = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 0.1f, 100.0f);
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
