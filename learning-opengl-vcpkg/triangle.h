#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <glad/glad.h>
#include "shader.h"

extern unsigned int indices[];

class Triangle {
public:
	unsigned int VAO; // vertex array object
	unsigned int VBO; // vertex buffer object
	unsigned int EBO; // element buffer object
	float* vertices;

	Shader* shader;

	Triangle(float vertices[],int size, Shader* shader);
	void render();

	~Triangle();
};

#endif