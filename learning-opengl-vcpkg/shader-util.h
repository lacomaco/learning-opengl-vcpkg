#ifndef SHADER_UTIL_H
#define SHADER_UTIL_H

#include <iostream>

char* readShaderSource(const char* shaderFilePath);

// shader ���α׷� id ��������.
unsigned int createShaderProgram(
	const char* shaderFilePath,
	int shaderType
);

#endif
