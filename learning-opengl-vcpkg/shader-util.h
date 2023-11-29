#ifndef SHADER_UTIL_H
#define SHADER_UTIL_H

#include <iostream>

char* readShaderSource(const char* shaderFilePath);

// shader 프로그램 id 리턴해줌.
unsigned int createShaderProgram(
	const char* shaderFilePath,
	int shaderType
);

#endif
