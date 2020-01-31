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

	// ������ɫ��
	//unsigned int shaderProgram = linkShader(genVertexShader(), genFragmentShader());
	Shader ourShader("vShader.txt", "fShader.txt");
	

	// ���������εĶ������ݺ���ɫ����
	//float vertices[] = {
	//	// λ��              // ��ɫ
	//	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
	//	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
	//	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	//};

	// ���������εĶ�������
	float vertices[] = 
	{
		// λ��              // ��ɫ
		0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,	// ���Ͻ�
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,	// ���½�
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	// ���½�
		-0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 1.0f	// ���Ͻ�
	};

	// ������������
	// ע��������0��ʼ! 
	unsigned int indices[] = 
	{ 
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};

	float texCoords[] = 
	{
		0.0f, 0.0f, // ���½�
		1.0f, 0.0f, // ���½�
		0.5f, 1.0f	// ����
	};
	
	// ����VAO��VBO��EBO
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 1. ��VAO
	glBindVertexArray(VAO);
	// 2. �Ѷ������鸴�Ƶ������й�OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// 3. �������ǵ��������鵽һ�����������У���OpenGLʹ��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. �趨��������ָ��
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// ���VBO
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	// ���VAO
	//glBindVertexArray(0);

	// ���EBO(���VAO֮ǰ���EBO�����VAO��EBO�����ݣ���˱����ڽ��VAO֮����EBO)
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		// ������
		processInput(window);

		// ��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(shaderProgram);
		ourShader.use();
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// ���VAO
		//glBindVertexArray(0);

		// ��鲢�����¼�����������
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ɾ��VAO��VBO
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

// ����
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
