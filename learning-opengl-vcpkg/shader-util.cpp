#include "shader-util.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

char* readShaderSource(const char* shaderFilePath) {
	std::string shaderCode;
	std::ifstream shaderFile;

	// 예외 처리 활성화
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		shaderFile.open(shaderFilePath);
		std::stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();
		shaderFile.close();

		shaderCode = shaderStream.str();
	} catch (std::ifstream::failure e) {
		std::cerr << shaderFilePath << " " << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		return nullptr;
	}

	char* dynamicShaderCode = new char[shaderCode.size() + 1];
	std::copy(shaderCode.begin(), shaderCode.end(), dynamicShaderCode);
	dynamicShaderCode[shaderCode.size()] = '\0';

	return dynamicShaderCode;
}

unsigned int createShaderProgram(const char* shaderFilePath, int shaderType
) {
	char* shaderSource = readShaderSource(shaderFilePath);
	unsigned int shaderId;

	shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shaderSource, NULL);
	glCompileShader(shaderId);

	int success;
	char infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		std::cout << shaderFilePath << " " << "ERROR SHADER COMPILATION FAILED" << infoLog << std::endl;
	}

	delete[] shaderSource;

	return shaderId;
}
