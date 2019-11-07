//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <iostream>
//
//#include "Shader.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#include "Camera.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);
//void mouse_callback(GLFWwindow* window, double xPos, double yPos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//
//// ???????
//const unsigned int SCR_WIDTH = 1280;
//const unsigned int SCR_HEIGHT = 720;
//
//float factor = 0.2f;
//float fov = 45.0f;
//
////?~{TE-=~}?
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// ?~{TE-=~}?
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//// ???
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//float vertices[] = {
//	-0.5f, -0.5f, -0.5f,
//	0.5f, -0.5f, -0.5f,
//	0.5f, 0.5f, -0.5f,
//	0.5f, 0.5f, -0.5f,
//	-0.5f, 0.5f, -0.5f,
//	-0.5f, -0.5f, -0.5f,
//
//	-0.5f, -0.5f, 0.5f,
//	0.5f, -0.5f, 0.5f,
//	0.5f, 0.5f, 0.5f, 
//	0.5f, 0.5f, 0.5f, 
//	-0.5f, 0.5f, 0.5f,
//	-0.5f, -0.5f, 0.5f, 
//
//	-0.5f, 0.5f, 0.5f,
//	-0.5f, 0.5f, -0.5f,
//	-0.5f, -0.5f, -0.5f,
//	-0.5f, -0.5f, -0.5f,
//	-0.5f, -0.5f, 0.5f, 
//	-0.5f, 0.5f, 0.5f, 
//
//	0.5f, 0.5f, 0.5f, 
//	0.5f, 0.5f, -0.5f, 
//	0.5f, -0.5f, -0.5f,
//	0.5f, -0.5f, -0.5f,
//	0.5f, -0.5f, 0.5f, 
//	0.5f, 0.5f, 0.5f, 
//
//	-0.5f, -0.5f, -0.5f,
//	0.5f, -0.5f, -0.5f, 
//	0.5f, -0.5f, 0.5f, 
//	0.5f, -0.5f, 0.5f, 
//	-0.5f, -0.5f, 0.5f, 
//	-0.5f, -0.5f, -0.5f,
//
//	-0.5f, 0.5f, -0.5f, 
//	0.5f, 0.5f, -0.5f,
//	0.5f, 0.5f, 0.5f, 
//	0.5f, 0.5f, 0.5f, 
//	-0.5f, 0.5f, 0.5f, 
//	-0.5f, 0.5f, -0.5f
//};
//
//int main() {
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lighting", NULL, NULL);
//	if (window == NULL) {
//		std::cout << "Failed to create GLFW window" << std::endl;
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	//?????????
//	glEnable(GL_DEPTH_TEST);
//
//	//????????????
//	Shader lightingShader("Shader.vs", "Shader.fs");
//	Shader lampShader("Shader.vs", "LampShader.fs");
//
//	//????????????
//	unsigned int VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	//?????????
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	//?????
//	while (!glfwWindowShouldClose(window)) {
//		//???????????~{]M~}???
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		processInput(window);
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		lightingShader.use();
//		lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
//		lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
//
//		//????
//		glm::mat4 projection;
//		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		lightingShader.setMat4("projection", glm::value_ptr(projection));
//
//		//????
//		glm::mat4 view;
//		view = camera.GetViewMatrix();
//		lightingShader.setMat4("view", glm::value_ptr(view));
//
//		//????1
//		glm::mat4 model;
//		lightingShader.setMat4("model", glm::value_ptr(model));
//
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		//????2
//		lampShader.use();
//		lampShader.setMat4("projection", glm::value_ptr(projection));
//		lampShader.setMat4("view", glm::value_ptr(view));
//		
//		glm::mat4 model2;
//		model2 = glm::translate(model2, lightPos);
//		model2 = glm::scale(model2, glm::vec3(0.2f));
//		lampShader.setMat4("model", glm::value_ptr(model2));
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glBindVertexArray(0);
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glfwTerminate();
//
//	return 0;
//}
//
//void processInput(GLFWwindow *window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//
//}
//
//void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
//	if (firstMouse) {
//		lastX = xPos;
//		lastY = yPos;
//		firstMouse = false;
//	}
//
//	float xoffset = lastX - xPos;	//?~{+O~}??????????????????????????????????????????????????????
//	float yoffset = lastY - yPos;	//???????????????????????????????????????????????????~{/R~}?????????????
//	lastX = xPos;
//	lastY = yPos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//
//}
//
////????????????
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
//	camera.ProcessMouseScroll(yoffset);
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
