#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <glad/glad.h>
#include "shader-util.h"

extern unsigned int TRIANGLE_SHADER_PROGRAM;

class Triangle {
public:
	unsigned int VAO;
	unsigned int VBO;
	float* vertices;
	Triangle(float vertices[],int size);
	void render();

	~Triangle();
};

#endif