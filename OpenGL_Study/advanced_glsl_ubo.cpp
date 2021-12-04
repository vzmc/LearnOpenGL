//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <stb_image.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <learnopengl/shader_m.h>
//#include <learnopengl/camera.h>
//#include <learnopengl/model.h>
//#include <learnopengl/filesystem.h>
//
//#include <iostream>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//void update_camera();
//unsigned int loadTexture(const char* path);
//unsigned int loadCubeMap(vector<std::string> faces);
//
//// settings
//const unsigned int SCR_WIDTH = 1280;
//const unsigned int SCR_HEIGHT = 720;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));
//float lastX = (float)SCR_WIDTH / 2.0;
//float lastY = (float)SCR_HEIGHT / 2.0;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//float cameraRadius = camera.Position.z;
//float cameraMoveSpeed = 1.0f;
//float cameraRotateSpeed = 2.0f;
//float cameraRotateAcceleration = 5.0f;
//
//int main()
//{
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//	// glfw window creation
//	// --------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	//glfwSetCursorPosCallback(window, mouse_callback);
//	//glfwSetScrollCallback(window, scroll_callback);
//
//	// tell GLFW to capture our mouse
//	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// glad: load all OpenGL function pointers
//	// ---------------------------------------
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// configure global opengl state
//	// -----------------------------
//	glEnable(GL_DEPTH_TEST);
//
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
//	glFrontFace(GL_CCW);
//
//	// build and compile shaders
//	// -------------------------
//	Shader reflectShader("reflect.vert", "reflect.frag");
//	Shader refractShader("reflect.vert", "refract.frag");
//	Shader skyboxShader("cubemap.vert", "cubemap.frag");
//	Shader screenShader("post_processing.vert", "post_processing.frag");
//
//	float cubeVertices[] = {
//		// Back face
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		// Front face
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		// Left face
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//		// Right face
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//		 // Bottom face
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//		// Top face
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f
//	};
//
//	float planeVertices[] = {
//		// positions          // texture Coords 
//		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
//
//		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f,
//		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f
//	};
//
//	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
//	// positions   // texCoords
//	-1.0f,  1.0f,  0.0f, 1.0f,
//	-1.0f, -1.0f,  0.0f, 0.0f,
//	 1.0f, -1.0f,  1.0f, 0.0f,
//
//	-1.0f,  1.0f,  0.0f, 1.0f,
//	 1.0f, -1.0f,  1.0f, 0.0f,
//	 1.0f,  1.0f,  1.0f, 1.0f
//	};
//
//	float skyboxVertices[] = {
//		// positions          
//		-1.0f,  1.0f, -1.0f,
//		-1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//		 1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//
//		-1.0f, -1.0f,  1.0f,
//		-1.0f, -1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f,  1.0f,
//		-1.0f, -1.0f,  1.0f,
//
//		 1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//
//		-1.0f, -1.0f,  1.0f,
//		-1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f, -1.0f,  1.0f,
//		-1.0f, -1.0f,  1.0f,
//
//		-1.0f,  1.0f, -1.0f,
//		 1.0f,  1.0f, -1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		-1.0f,  1.0f,  1.0f,
//		-1.0f,  1.0f, -1.0f,
//
//		-1.0f, -1.0f, -1.0f,
//		-1.0f, -1.0f,  1.0f,
//		 1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//		-1.0f, -1.0f,  1.0f,
//		 1.0f, -1.0f,  1.0f
//	};
//
//#pragma region 创建各种VAO
//	// cube VAO
//	unsigned int cubeVAO, cubeVBO;
//	glGenVertexArrays(1, &cubeVAO);
//	glGenBuffers(1, &cubeVBO);
//	glBindVertexArray(cubeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	// plane VAO
//	unsigned int planeVAO, planeVBO;
//	glGenVertexArrays(1, &planeVAO);
//	glGenBuffers(1, &planeVBO);
//	glBindVertexArray(planeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	// screen quad VAO
//	unsigned int quadVAO, quadVBO;
//	glGenVertexArrays(1, &quadVAO);
//	glGenBuffers(1, &quadVBO);
//	glBindVertexArray(quadVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//	// skybox
//	unsigned int skyboxVAO, skyboxVBO;
//	glGenVertexArrays(1, &skyboxVAO);
//	glGenBuffers(1, &skyboxVBO);
//	glBindVertexArray(skyboxVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//	glBindVertexArray(0);
//#pragma endregion
//
//	// load textures
//	// -------------
//	unsigned int cubeTexture = loadTexture(FileSystem::getPath("resources/textures/container.jpg").c_str());
//	unsigned int floorTexture = loadTexture(FileSystem::getPath("resources/textures/metal.png").c_str());
//
//	// skybox
//	// -------------
//	vector<std::string> faces
//	{
//		"resources/textures/skybox/right.jpg",
//		"resources/textures/skybox/left.jpg",
//		"resources/textures/skybox/top.jpg",
//		"resources/textures/skybox/bottom.jpg",
//		"resources/textures/skybox/front.jpg",
//		"resources/textures/skybox/back.jpg"
//	};
//	unsigned int cubemapTexture = loadCubeMap(faces);
//
//	// 加载一个模型
//	// -------------
//	Model aquaModel = Model(FileSystem::getPath("Akua/akua.pmx"));
//
//	// 配置uniform buffer object
//	// --------------------------
//	// 首先获取各个shader中block的Index
//	unsigned int uniformBlockIndexReflect = glGetUniformBlockIndex(reflectShader.ID, "Matrices");
//	unsigned int uniformBlockIndexRefract = glGetUniformBlockIndex(refractShader.ID, "Matrices");
//	unsigned int uniformBlockIndexSkybox = glGetUniformBlockIndex(skyboxShader.ID, "Matrices");
//	// 然后将他们block连接到绑定位置
//	glUniformBlockBinding(reflectShader.ID, uniformBlockIndexReflect, 0);
//	glUniformBlockBinding(refractShader.ID, uniformBlockIndexRefract, 0);
//	glUniformBlockBinding(skyboxShader.ID, uniformBlockIndexSkybox, 0);
//	// 生成实际的buffer
//	unsigned int uboMatrices;
//	glGenBuffers(1, &uboMatrices);
//	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
//	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
//	glBindBuffer(GL_UNIFORM_BUFFER, 0);
//	// 设置buffer的绑定位点
//	glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboMatrices);
//
//	// shader configuration
//	// --------------------
//	reflectShader.use();
//	reflectShader.setInt("skybox", 0);
//
//	refractShader.use();
//	refractShader.setInt("skybox", 0);
//
//	skyboxShader.use();
//	skyboxShader.setInt("skybox", 0);
//
//	screenShader.use();
//	screenShader.setInt("screenTexture", 0);
//
//#pragma region 帧缓存
//	// 创建一个帧缓存并绑定
//	unsigned int framebuffer;
//	glGenFramebuffers(1, &framebuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//
//	// 创建一个纹理
//	unsigned int texColorBuffer;
//	glGenTextures(1, &texColorBuffer);
//	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	// 将它附加到当前绑定的帧缓冲对象
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
//
//	// 创建一个渲染缓冲
//	unsigned int rbo;
//	glGenRenderbuffers(1, &rbo);
//	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//	// 附加到当前绑定的帧缓存对象
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
//
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//	{
//		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
//	}
//
//	// 解绑帧缓冲
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//#pragma endregion
//
//#pragma region 渲染循环
//	while (!glfwWindowShouldClose(window))
//	{
//		// per-frame time logic
//		// --------------------
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		// -----
//		processInput(window);
//		update_camera();
//
//		// render
//		// ------
//		// bind to framebuffer and draw scene as we normally would to color texture 
//		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//		glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
//
//		// make sure we clear the framebuffer's content
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//
//		glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
//		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
//		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
//
//		glm::mat4 model = glm::mat4(1.0f);
//
//		// draw objects       
//		reflectShader.use();
//		reflectShader.setVec3("cameraPos", camera.Position);
//		
//		// cubes
//		glBindVertexArray(cubeVAO);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//		model = glm::translate(model, glm::vec3(1.5f, 0.0f, -1.0f));
//		reflectShader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 1.0f));
//		reflectShader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		// model
//		refractShader.use();
//		refractShader.setVec3("cameraPos", camera.Position);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
//		model = glm::scale(model, glm::vec3(0.11f, 0.11f, 0.11f));
//		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//		refractShader.setMat4("model", model);
//		glDisable(GL_CULL_FACE);
//		aquaModel.Draw(refractShader);
//		glEnable(GL_CULL_FACE);
//		
//		// skybox
//		glDepthFunc(GL_LEQUAL);
//		skyboxShader.use();
//		glBindVertexArray(skyboxVAO);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glDepthFunc(GL_LESS);
//
//		// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
//		// clear all relevant buffers
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		screenShader.use();
//		glBindVertexArray(quadVAO);
//		glBindTexture(GL_TEXTURE_2D, texColorBuffer);	// use the color attachment texture as the texture of the quad plane
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		glBindVertexArray(0);
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//#pragma endregion
//
//	// optional: de-allocate all resources once they've outlived their purpose:
//	// ------------------------------------------------------------------------
//	glDeleteVertexArrays(1, &cubeVAO);
//	glDeleteVertexArrays(1, &planeVAO);
//	glDeleteVertexArrays(1, &quadVAO);
//	glDeleteVertexArrays(1, &skyboxVAO);
//
//	glDeleteBuffers(1, &cubeVBO);
//	glDeleteBuffers(1, &planeVBO);
//	glDeleteBuffers(1, &quadVBO);
//	glDeleteBuffers(1, &skyboxVBO);
//
//	glDeleteFramebuffers(1, &framebuffer);
//
//	glfwTerminate();
//	return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	/*if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);*/
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		cameraRadius -= cameraMoveSpeed * deltaTime;
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		cameraRadius += cameraMoveSpeed * deltaTime;
//
//	if (cameraRadius < 1.0f)
//	{
//		cameraRadius = 1.0f;
//	}
//	else if (cameraRadius > 100.0f)
//	{
//		cameraRadius = 100.0f;
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		cameraRotateSpeed -= cameraRotateAcceleration * deltaTime;
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		cameraRotateSpeed += cameraRotateAcceleration * deltaTime;
//
//	if (cameraRotateSpeed < 1.0f)
//	{
//		cameraRotateSpeed = 1.0f;
//	}
//	else if (cameraRotateSpeed > 360.0f)
//	{
//		cameraRotateSpeed = 360.0f;
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
//		camera.ChangeHeight(false, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
//		camera.ChangeHeight(true, deltaTime);
//
//	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
//		camera.ChangePitch(false, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
//		camera.ChangePitch(true, deltaTime);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}
//
//void update_camera()
//{
//	camera.updateCameraVectors();
//	camera.Position.x = -cos(glm::radians(camera.Yaw)) * cameraRadius;
//	camera.Position.z = -sin(glm::radians(camera.Yaw)) * cameraRadius;
//	camera.Yaw += cameraRotateSpeed * deltaTime;
//}
//
//// utility function for loading a 2D texture from file
//// ---------------------------------------------------
//unsigned int loadTexture(char const* path)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, nrComponents;
//	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data)
//	{
//		GLenum format;
//		if (nrComponents == 1)
//			format = GL_RED;
//		else if (nrComponents == 3)
//			format = GL_RGB;
//		else if (nrComponents == 4)
//			format = GL_RGBA;
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//
//	return textureID;
//}
//
//unsigned int loadCubeMap(vector<std::string> faces)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//	int width, height, nrChannels;
//	unsigned char* data;
//	for (unsigned int i = 0; i < faces.size(); i++)
//	{
//		data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
//		if (data)
//		{
//			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//			stbi_image_free(data);
//		}
//		else
//		{
//			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
//			stbi_image_free(data);
//		}
//	}
//
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//	return textureID;
//}
