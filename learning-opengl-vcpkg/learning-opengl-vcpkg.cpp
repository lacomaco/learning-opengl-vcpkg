﻿#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "triangle.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	std::cout <<"triangle 바깥에서 sizeof 측정 " << sizeof(vertices) << std::endl;

	Triangle* triangle1 = new Triangle(vertices,sizeof(vertices)/sizeof(float));

	// 임시 데이터
	float vertices2[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.9f, 0.0f
	};

	Triangle* triangle2 = new Triangle(vertices2,sizeof(vertices2)/sizeof(float));


	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		triangle1->render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	try {
		delete triangle1;
		delete triangle2;
	}catch(std::exception e){
		std::cout << e.what() << std::endl;
	}

	glfwTerminate();
	return 0;
}