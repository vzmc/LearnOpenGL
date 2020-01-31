#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
//unsigned int genVertexShader();
//unsigned int genFragmentShader();
//unsigned int linkShader(unsigned int, unsigned int);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 生成着色器
	//unsigned int shaderProgram = linkShader(genVertexShader(), genFragmentShader());
	Shader ourShader("vShader.txt", "fShader.txt");
	

	// 定义三角形的顶点数据和颜色数据
	//float vertices[] = {
	//	// 位置              // 颜色
	//	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
	//	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
	//	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	//};

	// 定义正方形的顶点数据
	float vertices[] = 
	{
		// 位置              // 颜色
		0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,	// 右上角
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,	// 右下角
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	// 左下角
		-0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 1.0f	// 左上角
	};

	// 定义索引数据
	// 注意索引从0开始! 
	unsigned int indices[] = 
	{ 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	float texCoords[] = 
	{
		0.0f, 0.0f, // 左下角
		1.0f, 0.0f, // 右下角
		0.5f, 1.0f	// 上中
	};
	
	// 生成VAO，VBO，EBO
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 1. 绑定VAO
	glBindVertexArray(VAO);
	// 2. 把顶点数组复制到缓冲中供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. 设定顶点属性指针
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// 解绑VBO
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	// 解绑VAO
	//glBindVertexArray(0);

	// 解绑EBO(解绑VAO之前解绑EBO会清除VAO中EBO的数据，因此必须在解绑VAO之后解绑EBO)
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		// 输入检测
		processInput(window);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(shaderProgram);
		ourShader.use();
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 解绑VAO
		//glBindVertexArray(0);

		// 检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 删除VAO和VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "witch = " << width << ", height = " << height << std::endl;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// 废弃
//unsigned int genVertexShader()
//{
//	const char* vertexShaderSource =
//		"#version 330 core\n"
//		"layout (location = 0) in vec3 v_position;\n"
//		"layout (location = 1) in vec3 v_color;\n"
//		"out vec3 v2f_color;\n"
//		"void main()\n"
//		"{\n"
//		"	v2f_color = v_color;\n"
//		"   gl_Position = vec4(v_position, 1.0);\n"
//		"}\0";
//
//	unsigned int vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//	int  success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	return vertexShader;
//}
//
//unsigned int genFragmentShader()
//{
//	const char* fragmentShaderSource = 
//		"#version 330 core\n"
//		"in vec3 v2f_color;\n"
//		"out vec4 FragColor;\n"
//		"void main()\n"
//		"{\n"
//		"   FragColor = vec4(v2f_color, 1.0);\n"
//		"}\0";
//
//	unsigned int fragmentShader;
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//
//	int  success;
//	char infoLog[512];
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	return fragmentShader;
//}
//
//unsigned int linkShader(unsigned int vertexShader, unsigned int fragmentShader)
//{
//	unsigned int shaderProgram;
//	shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//
//	// insert location binding code here
//	glBindAttribLocation(shaderProgram, 0, "vertex_position");
//	glBindAttribLocation(shaderProgram, 1, "vertex_colour");
//
//	glLinkProgram(shaderProgram);
//
//	int  success;
//	char infoLog[512];
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success)
//	{
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADERS::LINK_FAILED\n" << infoLog << std::endl;
//	}
//
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	return shaderProgram;
//}
