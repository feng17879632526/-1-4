
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include<iostream>
// ���ڳߴ�궨��
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


// ������ɫ������
const char* VSSOURCE =
"#version 330\n"
"\n"
"layout(location = 0) in vec3 iPos;\n"
"\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(iPos, 1);\n"
"}";

// ������ɫ������
const char* GSSOURCE =
"#version 330\n"
"\n"
"layout (triangles) in;\n"
"layout (triangle_strip, max_vertices = 3) out;\n"
"\n"
"out GSOUT_FSIN\n"
"{\n"
"    vec3 normal;\n"
"} gsOut;\n"
"\n"
"uniform mat4 mMat;\n"
"uniform mat4 vMat;\n"
"uniform mat4 pMat;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 worldA = mMat * gl_in[0].gl_Position;\n"
"    vec4 worldB = mMat * gl_in[1].gl_Position;\n"
"    vec4 worldC = mMat * gl_in[2].gl_Position;\n"
"    \n"
"    vec3 a = worldB.xyz - worldA.xyz;\n"
"    vec3 b = worldC.xyz - worldA.xyz;\n"
"    vec3 n = normalize(cross(a, b));\n"
"    \n"
"    gl_Position = pMat * vMat * worldA;\n"
"    gsOut.normal = n;\n"
"    EmitVertex();\n"
"    \n"
"    gl_Position = pMat * vMat * worldB;\n"
"    gsOut.normal = n;\n"
"    EmitVertex();\n"
"    \n"
"    gl_Position = pMat * vMat * worldC;\n"
"    gsOut.normal = n;\n"
"    EmitVertex();\n"
"    \n"
"    EndPrimitive();\n"
"}";

// ƬԪ��ɫ������
const char* FSSOURCE =
"#version 330\n"
"in GSOUT_FSIN\n"
"{\n"
"    vec3 normal;\n"
"} fsIn;\n"
"uniform vec3 faceColor;\n"
"uniform vec3 lightColor;\n"
"uniform vec3 lightDirection;\n"
"uniform vec3 viewDirection;\n"
"uniform bool hasLight;\n"
"\n"
"float ambient = 0.2;\n"
"float shininess = 128.0;\n"
"\n"
"void main()\n"
"{\n"
"    if (hasLight)\n"
"    {\n"
"		 vec3 fragNormal = normalize(fsIn.normal);\n"
"        \n"
"		 vec3 invertLightDir = normalize(-lightDirection);\n"
"		 vec3 invertViewDir = normalize(-viewDirection);\n"
"		 \n"
"		 float diffuse = max(dot(invertLightDir, fragNormal), 0.0);\n"
"		 \n"
"		 vec3 halfVec = normalize(invertViewDir + invertLightDir);\n"
"		 float specular = 0.3 * pow(max(dot(fragNormal, halfVec), 0.0), shininess);\n"
"		 \n"
"		 gl_FragColor = vec4(faceColor * (ambient + diffuse) + specular * lightColor, 1.0);\n"
"    }\n"
"    else\n"
"	    gl_FragColor = vec4(faceColor, 1);\n"
"}";

// ����ȫ�ֱ���
unsigned int MyShaderProgram;
unsigned int PVBO, CVBO, VAO, EBO;
glm::mat4 mMat, vMat, pMat;

// ģ������
//int VNB = 8;
int VNB = 6;
float MyPoints[] = {
	//-0.5f, -0.5f, 0.5f,  // bottom left
	//0.5f, -0.5f, 0.5f,   // bottom right
	//0.5f,  0.5f, 0.5f,   // top right
	//-0.5f,  0.5f, 0.5f,   // top left 
	//-0.5f, -0.5f, -0.5f,  // bottom left
	//0.5f, -0.5f, -0.5f,   // bottom right
	//0.5f,  0.5f, -0.5f,   // top right
	//-0.5f,  0.5f, -0.5f   // top left 
	0.5f,0.0f,0.0f,   //+x
	0.0f,0.5f,0.0f,    //+y
	0.0f,0.0f,0.5f,    //+z
	-0.5f,0.0f,0.0f,   //-x
	0.0f,-0.5f,0.0f,    //-y
	0.0f,0.0f,-0.5f,    //-z
};

//int FNB = 12;
int FNB = 8;
int MyIndices[] = {
	//0, 1, 2,
	//0, 2, 3,
	//1, 5, 6,
	//1, 6, 2,
	//5, 4, 7,
	//5, 7, 6,
	//4, 0, 3,
	//4, 3, 7,
	//2, 6, 7,
	//2, 7, 3,
	//0, 1, 5,
	//0, 5, 4
	0,1,2,
	0,1,5,
	1,2,3,
	1,2,5,
	0,4,2,
	0,4,5,
	3,4,2,
	3,4,5
};

void resize_window(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);

	pMat = glm::mat4(1.0f);
	float ratio = (float)w / (float)h;
	pMat = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);

	glUseProgram(MyShaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(MyShaderProgram, "pMat"), 1, GL_FALSE, &pMat[0][0]);
}

void init_shaders()
{
	// ���ɶ�����ɫ��
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VSSOURCE, NULL);
	glCompileShader(vertexShader);

	// ���ɼ�����ɫ��
	unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometryShader, 1, &GSSOURCE, NULL);
	glCompileShader(geometryShader);

	// ����ƬԪ��ɫ��
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FSSOURCE, NULL);
	glCompileShader(fragmentShader);

	// ������ɫ���γ�С����
	MyShaderProgram = glCreateProgram();
	glAttachShader(MyShaderProgram, vertexShader);
	glAttachShader(MyShaderProgram, geometryShader);
	glAttachShader(MyShaderProgram, fragmentShader);
	glLinkProgram(MyShaderProgram);

	// ������Ϻ���ɫ����ɾ��
	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);
}

void bind_data()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &PVBO); // PVBO ������
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// ���ڴ��еĶ����������ݴ��䵽�Դ�� PVBO ��
	glBindBuffer(GL_ARRAY_BUFFER, PVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * VNB, MyPoints, GL_STATIC_DRAW);

	// ��������ɫ����locationΪ0��λ�ð�����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ���ڴ��е��������������ݴ��䵽�Դ�� EBO ��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3 * FNB, MyIndices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
float scale = 0.2f;
float rotatex = 0.5f, rotatey = 0.5f, rotatez = 0.5f;
void display()
{
	// ��֡������ɫ����ΪĬ����ɫ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ������Ȳ���
	glEnable(GL_DEPTH_TEST);

	glUseProgram(MyShaderProgram);
	glBindVertexArray(VAO);

	static int frame = 0;
	float theta = glm::radians(frame * 60 / 360.0f) * 2;

	float color[3] = { 0.9f, 0.45f, 0.2f };
	for (int j = -1; j < 2; ++j)
	{
		for (int i = -1; i < 2; ++i)
		{
			if (i == 1 && j == 1 || i == -1 && j == -1 || i == -1 && j == 1 || i == 1 && j == -1)continue;
			mMat = glm::mat4(1.0f);
			mMat = glm::scale(mMat, glm::vec3(scale, scale, scale));
			mMat = glm::rotate(mMat, theta, glm::vec3(rotatex, rotatey, rotatez));
			mMat = glm::translate(mMat, glm::vec3(float(i) * 1, float(j) * 1, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(MyShaderProgram, "mMat"), 1, GL_FALSE, &mMat[0][0]);

			color[0] += 0.3f;
			if (color[0] > 1.0f)
				color[0] = 0.1f;

			color[1] += 0.3f;
			if (color[1] > 1.0f)
				color[1] = 0.3f;

			color[2] += 0.3f;
			if (color[2] > 1.0f)
				color[2] = 0.2f;

			glUniform3fv(glGetUniformLocation(MyShaderProgram, "faceColor"), 1, color);
			glDrawElements(GL_TRIANGLES, 3 * FNB, GL_UNSIGNED_INT, 0);
		}
	}

	++frame;

	glDisable(GL_DEPTH_TEST);
}

void process_input(GLFWwindow* window)
{
	static bool light = false;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		light = !light;
		glUniform1i(glGetUniformLocation(MyShaderProgram, "hasLight"), (int)light);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		for (int i = 0; i < 6; i++) {
			MyPoints[i * 3] += 0.005;
		}
		bind_data();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		for (int i = 0; i < 6; i++) {
			MyPoints[i * 3] -= 0.005;
		}
		bind_data();
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		for (int i = 0; i < 6; i++) {
			MyPoints[i * 3+1] += 0.005;
		}
		bind_data();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		for (int i = 0; i < 6; i++) {
			MyPoints[i * 3+1] -= 0.005;
		}
		bind_data();
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		rotatex += 0.05;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		rotatex -= 0.05;
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		rotatey += 0.05;
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		rotatey -= 0.05;
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		rotatez += 0.05;
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		rotatez -= 0.05;
	}
}

void scroll_callback(GLFWwindow* win, double xoffset, double yoffset) {
	//printf("�����֣�xoffset=%8.2f,yoffset=%8.2f\n", xoffset, yoffset);
	scale += 0.05*yoffset;
}

int main(void)
{
	// ��ʼ�� GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ��֧�̶ֹ�����

	// ��������
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, u8"��С��8002119102", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}

	// ������ӳ�䵽OpenGL֡����
	glfwMakeContextCurrent(window);

	// ע�ᴰ�ڴ�С�ı�ʱ�Ļص�����Ϊ resize_window
	glfwSetFramebufferSizeCallback(window, resize_window);

	// ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		return -1;
	}

	// ������ɫ������
	init_shaders();

	// ������
	bind_data();

	// ����֡�����Ĭ����ɫ�������ڵı�����ɫ��
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

	// ���ö���Ĵ�СΪ10���ؿ�
	glPointSize(10.0f);

	// ��ʼ��ģ�͡���ͼ��ͶӰ����
	mMat = glm::mat4(1.0f);
	vMat = glm::mat4(1.0f);
	pMat = glm::mat4(1.0f);

	vMat = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	float ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	pMat = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);

	glUseProgram(MyShaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(MyShaderProgram, "mMat"), 1, GL_FALSE, &mMat[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(MyShaderProgram, "vMat"), 1, GL_FALSE, &vMat[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(MyShaderProgram, "pMat"), 1, GL_FALSE, &pMat[0][0]);

	float lightColor[3] = { 1.0f, 1.0f, 1.0f };
	glUniform3fv(glGetUniformLocation(MyShaderProgram, "lightColor"), 1, lightColor);
	float lightDir[3] = { -1.0f, -1.0f, -1.0f };
	glUniform3fv(glGetUniformLocation(MyShaderProgram, "lightDirection"), 1, lightDir);
	float viewDir[3] = { 0.0f, 0.0f, -1.0f };
	glUniform3fv(glGetUniformLocation(MyShaderProgram, "viewDirection"), 1, viewDir);

	// ������
	glfwSetScrollCallback(window, scroll_callback);
	// ����ѭ��
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
