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
//int p = 0,num=0,newNum=0; //p��¼���ο򶥵���,num��¼����ζ�����,newNum��¼�ü���Ķ���εĶ�����
//void addPoint(float x, float y,float color1, float color2, float color3) {
//	int k = 3 * VNB;
//	MyPoints[k] = x;
//	MyColors[k++] = color1;
//	MyPoints[k] = y;
//	MyColors[k++] = color2;
//	MyPoints[k] = 0;
//	MyColors[k++] = color3;
//	VNB++;
//}
//void addLine(float x1, float y1, float x2, float y2, float color1, float color2, float color3) {
//	addPoint(x1, y1, color1, color2, color3);
//	addPoint(x2, y2, color1, color2, color3);
//}
//int op; //��¼ѡ��
//void display()
//{
//	// ��֡������ɫ����ΪĬ����ɫ
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glUseProgram(MyShaderProgram);
//	glBindVertexArray(VAO);
//	// ����������
//	glDrawArrays(GL_LINE_LOOP, 0, p); //p��¼���Ǿ�������Ķ�������4����
//	if (op == 1 || op == 2) {
//		//���ü�����߶�
//		glDrawArrays(GL_LINES, p, VNB - p);  //����������p��ʼ����VNB-p����(�ӵ�p�����㿪ʼ��VNB-p������)���ڶ������������������������Ƕ��㣨��������Ϊ1���㣩
//	}
//	else if (op == 3) {
//		glDrawArrays(GL_TRIANGLE_FAN, p, num);   //��ԭʼ�����
//		glDrawArrays(GL_TRIANGLE_FAN, p+num, VNB-p-num);//���ü���Ķ����
//	}
//	//glDrawElements(GL_LINE, 2, GL_UNSIGNED_INT, 0);
//	// ������
//	//glDrawArrays(GL_POINTS, 0, VNB);
//}
//
//void process_input(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}
//
//float xmin, ymin, xmax, ymax;// ��¼�ü�����
//void showClippingWindows(float color1,float color2,float color3){
//	addPoint(xmin, ymin, color1, color2, color3);
//	addPoint(xmax, ymin, color1, color2, color3);
//	addPoint(xmax, ymax, color1, color2, color3);
//	addPoint(xmin, ymax, color1, color2, color3);
//	p = VNB;
//}
//
//#define LEFT 1 
//#define RIGHT 2
//#define BOTTOM 4
//#define TOP 8
////�õ�ĳ�����������
//int getCode(float x, float y) {
//	int code = 0;
//	if (x < xmin) {
//		code = LEFT | code;
//	}
//	else if (x > xmax) {
//		code = RIGHT | code;
//	}
//	if (y < ymin) {
//		code = BOTTOM | code;
//	}
//	else if (y > ymax) {
//		code = TOP | code;
//	}
//	return code;
//}
//void Cohen_Sutherland(float x1,float y1,float x2,float y2) {
//	addLine(x1, y1, x2, y2, 0, 1, 0);  //�Ȼ���ԭֱ��
//	int code, code1, code2;
//	float x, y;
//	code1 = getCode(x1, y1);  //��ñ��� 
//	code2 = getCode(x2, y2);
//
//	while (code1 != 0 || code2 != 0)
//	{
//		if (code1 & code2)
//			return;
//		if (code1)
//			code = code1;
//		else
//			code = code2;
//
//		if (LEFT & code)  //����봰�ڱ߽�Ľ���
//		{
//			x = xmin;
//			y = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
//		}
//		else if (RIGHT & code)
//		{
//			x = xmax;
//			y = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
//		}
//		else if (BOTTOM & code)
//		{
//			y = ymin;
//			x = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
//		}
//		else if (TOP & code)
//		{
//			y = ymax;
//			x = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
//		}
//		if (code == code1) //����codeֵ
//		{
//			x1 = x;
//			y1 = y;
//			code1 = getCode(x1, y1);
//		}
//		else
//		{
//			x2 = x;
//			y2 = y;
//			code2 = getCode(x2, y2);
//		}
//	}
//	addLine(x1, y1, x2, y2,1,0,0);
//}
//void Liang_Barsky(float x1, float y1, float x2, float y2) {
//	addLine(x1, y1, x2, y2, 0, 1, 0);  //�Ȼ���ԭֱ��
//
//	float dx = x2 - x1, dy = y2 - y1,umin,umax,uminx,umaxx,uminy,umaxy;
//	float ul = (xmin - x1) / dx, ur = (xmax - x1) / dx, ub = (ymin - y1) / dy, ut = (ymax - y1) / dy;
//	if (dx == 0) {
//		if (x1<xmin || x1>xmax) {
//			return;
//		}
//		else {
//			umin = min(ub, ut), umax = max(ub, ut);
//			if (umax < 0 || umin>1)return;
//			else {
//				umin = max(umin, 0.0f);
//				umax = min(umax, 1.0f);
//			}
//		}
//	}
//	else if (dy == 0) {
//		if (y1<ymin || y1>ymax) {
//			return;
//		}
//		else {
//			umin = min(ul, ur), umax = max(ul, ur);
//			if (umax < 0 || umin>1)return;
//			else {
//				umin = max(umin, 0.0f);
//				umax = min(umax, 1.0f);
//			}
//		}
//	}
//	else if (dx > 0 && dy > 0) {
//		umin = max(ul, ub), umax = min(ur, ut);
//		if (umax < 0 || umin>1)return;
//		else {
//			umin = max(umin, 0.0f);
//			umax = min(umax, 1.0f);
//		}
//	}
//	else if (dx < 0 && dy > 0) {
//		umin = max(ur, ub), umax = min(ul, ut);
//		if (umax < 0 || umin>1)return;
//		else {
//			umin = max(umin, 0.0f);
//			umax = min(umax, 1.0f);
//		}
//	}
//	else if (dx > 0 && dy < 0) {
//		umin = max(ul, ut), umax = min(ur, ub);
//		if (umax < 0 || umin>1)return;
//		else {
//			umin = max(umin, 0.0f);
//			umax = min(umax, 1.0f);
//		}
//	}
//	else if (dx < 0 && dy < 0) {
//		umin = max(ur, ut), umax = min(ul, ub);
//		if (umax < 0 || umin>1)return;
//		else {
//			umin = max(umin, 0.0f);
//			umax = min(umax, 1.0f);
//		}
//	}
//	if (umax < umin)return;
//	else {
//		uminx = x1 + umin * (x2 - x1);
//		umaxx = x1 + umax * (x2 - x1);
//		uminy = y1 + umin * (y2 - y1);
//		umaxy = y1 + umax * (y2 - y1);
//	}
//	addLine(uminx, uminy, umaxx, umaxy, 1, 0, 0);
//}
//float poly[2000]; //�������Ķ�ά����ζ�������
//void addPolygon(float*vec, int num,float color1, float color2, float color3) {
//	for (int i = 0; i < num; i++) {
//		addPoint(vec[i * 2], vec[i * 2 + 1], color1, color2, color3);
//	}
//}
//
//void left_clip() {
//	int i, j = 0, count = 0;
//	float temp[2000], x1, y1, x2, y2;
//	for (i = 0; i < 2 * newNum; i += 2) {
//		x1 = poly[i];
//		y1 = poly[i + 1];
//		x2 = poly[i + 2];
//		y2 = poly[i + 3];
//		if (x1 < xmin && x2 < xmin) {
//			//both points outside. Do not store any vertices
//		}
//		else if (x1 > xmin && x2 > xmin) {
//			//both points inside. Store second vertex
//			temp[j] = x2;
//			temp[j + 1] = y2;
//			j += 2;
//			count++;
//		}
//		else if (x1<xmin && x2>xmin) {
//			//outside to inside. Store intersection newNum second vertex
//			float x = xmin;
//			float y = y1 + (xmin - x1) * (float)(y2 - y1) / (x2 - x1);
//			temp[j] = x;
//			temp[j + 1] = y;
//			temp[j + 2] = x2;
//			temp[j + 3] = y2;
//			j += 4;
//			count += 2;
//		}
//		else {
//			//inside to outside. Store intersection only
//			float x = xmin;
//			float y = y1 + (xmin - x1) * (float)(y2 - y1) / (x2 - x1);
//			temp[j] = x;
//			temp[j + 1] = y;
//			j += 2;
//			count++;
//		}
//	}
//	newNum = count;
//	//store 1st vertex as last
//	temp[j] = temp[0];
//	temp[j + 1] = temp[1];
//
//	for (i = 0; i < 2 * (newNum + 1); i++)
//		poly[i] = temp[i];
//}
//void right_clip() {
//	int i, j = 0, count = 0;
//	float temp[2000], x1, y1, x2, y2;
//	for (i = 0; i < 2 * newNum; i += 2) {
//		x1 = poly[i];
//		y1 = poly[i + 1];
//		x2 = poly[i + 2];
//		y2 = poly[i + 3];
//		if (x1 > xmax && x2 > xmax) {
//			//both points outside. Do not store any vertices
//		}
//		else if (x1 < xmax && x2 < xmax) {
//			//both points inside. Store second vertex
//			temp[j] = x2;
//			temp[j + 1] = y2;
//			j += 2;
//			count++;
//		}
//		else if (x1 > xmax && x2 < xmax) {
//			//outside to inside. Store intersection newNum second vertex
//			float x = xmax;
//			float y = y1 + (xmax - x1) * (float)(y2 - y1) / (x2 - x1);
//			temp[j] = x;
//			temp[j + 1] = y;
//			temp[j + 2] = x2;
//			temp[j + 3] = y2;
//			j += 4;
//			count += 2;
//		}
//		else {
//			//inside to outside. Store intersection only
//			float x = xmax;
//			float y = y1 + (xmax - x1) * (float)(y2 - y1) / (x2 - x1);
//			temp[j] = x;
//			temp[j + 1] = y;
//			j += 2;
//			count++;
//		}
//	}
//	newNum = count;
//	//store 1st vertex as last
//	temp[j] = temp[0];
//	temp[j + 1] = temp[1];
//
//	for (i = 0; i < 2 * (newNum + 1); i++)
//		poly[i] = temp[i];
//}
//void bottom_clip() {
//	int i, j = 0, count = 0;
//	float temp[2000], x1, y1, x2, y2;
//	for (i = 0; i < 2 * newNum; i += 2) {
//		x1 = poly[i];
//		y1 = poly[i + 1];
//		x2 = poly[i + 2];
//		y2 = poly[i + 3];
//		if (y1 < ymin && y2 < ymin) {
//			//both points outside. Do not store any vertices
//		}
//		else if (y1 > ymin && y2 > ymin) {
//			//both points inside. Store second vertex
//			temp[j] = x2;
//			temp[j + 1] = y2;
//			j += 2;
//			count++;
//		}
//		else if (y1 < ymin && y2 > ymin) {
//			//outside to inside. Store intersection newNum second vertex
//			float x = x1 + (ymin - y1) / ((float)(y2 - y1) / (x2 - x1));
//			float y = ymin;
//			temp[j] = x;
//			temp[j + 1] = y;
//			temp[j + 2] = x2;
//			temp[j + 3] = y2;
//			j += 4;
//			count += 2;
//		}
//		else {
//			//inside to outside. Store intersection only
//			float x = x1 + (ymin - y1) / ((float)(y2 - y1) / (x2 - x1));
//			float y = ymin;
//			temp[j] = x;
//			temp[j + 1] = y;
//			j += 2;
//			count++;
//		}
//	}
//	newNum = count;
//	//store 1st vertex as last
//	temp[j] = temp[0];
//	temp[j + 1] = temp[1];
//
//	for (i = 0; i < 2 * (newNum + 1); i++)
//		poly[i] = temp[i];
//}
//void top_clip() {
//	int i, j = 0, count = 0;
//	float temp[2000], x1, y1, x2, y2;
//	for (i = 0; i < 2 * newNum; i += 2) {
//		x1 = poly[i];
//		y1 = poly[i + 1];
//		x2 = poly[i + 2];
//		y2 = poly[i + 3];
//		if (y1 > ymax && y2 > ymax) {
//			//both points outside. Do not store any vertices
//		}
//		else if (y1 < ymax && y2 < ymax) {
//			//both points inside. Store second vertex
//			temp[j] = x2;
//			temp[j + 1] = y2;
//			j += 2;
//			count++;
//		}
//		else if (y1>ymax && y2<ymax) {
//			//outside to inside. Store intersection newNum second vertex
//			float x = x1 + (ymax - y1) / ((float)(y2 - y1) / (x2 - x1));
//			float y = ymax;
//			temp[j] = x;
//			temp[j + 1] = y;
//			temp[j + 2] = x2;
//			temp[j + 3] = y2;
//			j += 4;
//			count += 2;
//		}
//		else {
//			//inside to outside. Store intersection only
//			float x = x1 + (ymax - y1) / ((float)(y2 - y1) / (x2 - x1));
//			float y = ymax;
//			temp[j] = x;
//			temp[j + 1] = y;
//			j += 2;
//			count++;
//		}
//	}
//	newNum = count;
//	//store 1st vertex as last
//	temp[j] = temp[0];
//	temp[j + 1] = temp[1];
//
//	for (i = 0; i < 2 * (newNum + 1); i++)
//		poly[i] = temp[i];
//}
//void Sutherland_Hodgman() {
//	addPolygon(poly,num,0, 1, 0);  //���ԭʼ����εĶ������ɫ����
//	poly[2 * newNum] = poly[0];
//	poly[2 * newNum + 1] = poly[1];
//	left_clip();
//	right_clip();
//	bottom_clip();
//	top_clip();
//
//	addPolygon(poly,newNum, 1, 0, 0); //��Ӳü������εĶ������ɫ����
//}
//int main(void)
//{
//	float x1, y1, x2, y2;
//	cout << "1.Cohen-Sutherland" << endl;
//	cout << "2.Liang-Barsky" << endl;
//	cout << "3.Sutherland-Hodgeman" << endl;
//	cout << "Please input your choice:";
//	cin >> op;
//	//op = 3;
//
//	cout << "Please enter the lower left and upper right vertices of the rectangle area:" << endl;;
//	cin >> xmin >> ymin >> xmax >> ymax;
//	//xmin = 20, ymin = 20, xmax = 80, ymax = 80;
//	showClippingWindows(0.5,0.5,0.5);
//	switch(op) {
//		case 1:
//			cout << "Please enter two endpoints of the line segment:" << endl;
//			cin >> x1 >> y1 >> x2 >> y2;
//			Cohen_Sutherland(x1, y1, x2, y2);
//			break;
//		case 2:
//			cout << "Please enter two endpoints of the line segment:" << endl;
//			cin >> x1 >> y1 >> x2 >> y2;
//			//x1 = 10, y1 = 70, x2 = 50, y2 = 50;
//			Liang_Barsky(x1, y1, x2, y2);
//			break;
//		case 3:
//			cout << "Please enter the number of vertices of the polygon��" << endl;
//			cin >> num;
//			//num = 5;
//			newNum = num; //newNum��¼��ǰ����εĶ�����
//			cout << "Please enter the vertices of the polygon��" << endl;
//			for (int i = 0; i < num; i++) {
//				cin >> poly[2 * i];
//				cin >> poly[2 * i + 1];
//			}
//			//poly[0] = 10;
//			//poly[1] = 10;
//
//			//poly[2] = 30;
//			//poly[3] = 10;
//
//			//poly[4] = 90;
//			//poly[5] = 20;
//
//			//poly[6] = 30;
//			//poly[7] = 60;
//
//			//poly[8] = 10;
//			//poly[9] = 60;
//			Sutherland_Hodgman();
//			break;
//	} 
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
//	pMat = glm::ortho(0.0f, ratio*100, 0.0f, 100.0f, 0.0f, 100.0f);  //��Ϊ����ͶӰ����۲죬���޸�ͶӰ����ʹ��������0��100�ĵ����ڴ�����(������0~133.3)
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
