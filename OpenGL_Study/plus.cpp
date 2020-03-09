#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Camera.h"
#include "stb_image.h"
#include "Model.h"


// 函数定义
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
GLuint loadTexture(const char*);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
glm::mat4 getModelMat4(glm::vec3 translate = glm::vec3(0.0f), glm::vec3 rotate = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(0.0f));
glm::mat4 getViewMat4();
glm::mat4 getProjectionMat4();
void initSpotLights(Shader& lightingShader, glm::vec3 positions[]);
void updateSpotLights(Shader& lightingShader, glm::vec3 positions[]);

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// 时间
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

bool isSpotLightOn = false;
bool isKeyHat = false;

int main()
{
	Model model("nanosuit/nanosuit.obj");

	srand((unsigned)time(NULL));

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << version << std::endl;

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	float vertices[] =
	{
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	// positions of the point lights
	glm::vec3 spotLightPositions[] =
	{
		glm::vec3(0.15f, 0.0f, 5.0f),
		glm::vec3(-0.15f, 0.0f, 5.0f),
	};

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// load and create textures
	// -------------------------
	GLuint diffuseMap = loadTexture("container2.png");
	GLuint specularMap = loadTexture("container2_specular.png");
	GLuint aweiMap = loadTexture("plus.png");

	// build and compile our shader zprogram
	// ------------------------------------
	Shader lampShader("light.vert", "light.frag");
	Shader lightingShader("object.vert", "object.frag");

	lightingShader.use();
	lightingShader.setInt("material.diffuse", 0);
	lightingShader.setInt("material.specular", 1);
	lightingShader.setInt("awei", 2);
	lightingShader.setFloat("material.shininess", 32.0f);

	// directional light
	lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

	initSpotLights(lightingShader, spotLightPositions);

	// 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// also clear the depth buffer now!

		
		// 绑定贴图
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, aweiMap);

		glBindVertexArray(VAO);

		// 绘制光源立方体对象
		lampShader.use();
		lampShader.setMat4("view", camera.GetViewMatrix());
		lampShader.setMat4("projection", getProjectionMat4());
		lampShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

		for (unsigned int i = 0; i < 2; i++)
		{
			lampShader.setMat4("model", getModelMat4(spotLightPositions[i], glm::vec3(0.0f), glm::vec3(0.2f)));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// 绘制画框
		lightingShader.use();
		lightingShader.setVec3("viewPos", camera.Position);
		lightingShader.setMat4("view", camera.GetViewMatrix());
		lightingShader.setMat4("projection", getProjectionMat4());	
		lightingShader.setMat4("model", getModelMat4(glm::vec3(0.0f, 0.0f, -0.5f), glm::vec3(), glm::vec3(5.0f)));

		updateSpotLights(lightingShader, spotLightPositions);
		
		glDrawArrays(GL_TRIANGLES, 6, 6);
		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 删除VAO和VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

GLuint loadTexture(const char* path)
{
	GLuint textureID = 0;
	// 生成纹理
	glGenTextures(1, &textureID);

	// 加载并生成纹理
	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = 0;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	return textureID;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "witch = " << width << ", height = " << height << std::endl;
	glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && isKeyHat == false)
	{
		isKeyHat = true;
		isSpotLightOn = !isSpotLightOn;
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE)
	{
		isKeyHat = false;
	}
}

glm::mat4 getModelMat4(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, translate);
	model = glm::rotate(model, rotate.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, rotate.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotate.z, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);

	return model;
}

glm::mat4 getViewMat4()
{
	glm::mat4 view(1.0f); // = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	return view;
}

glm::mat4 getProjectionMat4()
{
	glm::mat4 projection(1.0);
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);

	return projection;
}

void initSpotLights(Shader& lightingShader, glm::vec3 positions[])
{
	lightingShader.setVec3("spotLights[0].position", positions[0]);
	lightingShader.setVec3("spotLights[0].ambient", 0.0f, 0.0f, 0.0f);
	lightingShader.setVec3("spotLights[0].diffuse", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("spotLights[0].specular", 1.0f, 1.0f, 1.0f);
	lightingShader.setFloat("spotLights[0].constant", 1.0f);
	lightingShader.setFloat("spotLights[0].linear", 0.09);
	lightingShader.setFloat("spotLights[0].quadratic", 0.032);
	lightingShader.setFloat("spotLights[0].cutOff", glm::cos(glm::radians(15.0f)));
	lightingShader.setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(20.0f)));
	lightingShader.setBool("spotLights[0].isOn", true);

	lightingShader.setVec3("spotLights[1].position", positions[1]);
	lightingShader.setVec3("spotLights[1].ambient", 0.0f, 0.0f, 0.0f);
	lightingShader.setVec3("spotLights[1].diffuse", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("spotLights[1].specular", 1.0f, 1.0f, 1.0f);
	lightingShader.setFloat("spotLights[1].constant", 1.0f);
	lightingShader.setFloat("spotLights[1].linear", 0.09);
	lightingShader.setFloat("spotLights[1].quadratic", 0.032);
	lightingShader.setFloat("spotLights[1].cutOff", glm::cos(glm::radians(15.0f)));
	lightingShader.setFloat("spotLights[1].outerCutOff", glm::cos(glm::radians(20.0f)));
	lightingShader.setBool("spotLights[1].isOn", true);

	// 自己控制的
	lightingShader.setVec3("spotLights[2].ambient", 0.0f, 0.0f, 0.0f);
	lightingShader.setVec3("spotLights[2].diffuse", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("spotLights[2].specular", 1.0f, 1.0f, 1.0f);
	lightingShader.setFloat("spotLights[2].constant", 1.0f);
	lightingShader.setFloat("spotLights[2].linear", 0.09);
	lightingShader.setFloat("spotLights[2].quadratic", 0.032);
	lightingShader.setFloat("spotLights[2].cutOff", glm::cos(glm::radians(15.0f)));
	lightingShader.setFloat("spotLights[2].outerCutOff", glm::cos(glm::radians(20.0f)));
	lightingShader.setBool("spotLights[2].isOn", isSpotLightOn);
}

void updateSpotLights(Shader& lightingShader, glm::vec3 positions[])
{
	glm::vec3 target0 = glm::vec3(glm::sin(glfwGetTime()) * 3.0f, -glm::abs(glm::cos(glfwGetTime()) * 2.5f) + 3.0f, 0.0f);
	glm::vec3 target1 = glm::vec3(glm::sin(glfwGetTime() + glm::radians(180.0f)) * 3.0f, glm::abs(glm::cos(glfwGetTime()) * 2.5f) - 3.0f, 0.0f);

	lightingShader.setVec3("spotLights[0].direction", target0 - positions[0]);
	lightingShader.setVec3("spotLights[1].direction", target1 - positions[1]);
	
	lightingShader.setVec3("spotLights[2].position", camera.Position);
	lightingShader.setVec3("spotLights[2].direction", camera.Front);

	lightingShader.setBool("spotLights[2].isOn", isSpotLightOn);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "xpos = " << xpos << ", ypos = " << ypos << std::endl;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = lastX - xpos;
	float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

