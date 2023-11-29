#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <glad/glad.h>
#include "shader-util.h"

extern unsigned int TRIANGLE_SHADER_PROGRAM;
extern unsigned int indices[];

class Triangle {
public:
	unsigned int VAO; // vertex array object
	unsigned int VBO; // vertex buffer object
	unsigned int EBO; // element buffer object
	float* vertices;

	Triangle(float vertices[],int size);
	void render();

	~Triangle();
};

#endif