#include "shader.h"

char* Shader::readShaderSource(const char* shaderFilePath) {
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
	}
	catch (std::ifstream::failure e) {
		std::cerr << shaderFilePath << " " << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		return nullptr;
	}

	char* dynamicShaderCode = new char[shaderCode.size() + 1];
	std::copy(shaderCode.begin(), shaderCode.end(), dynamicShaderCode);
	dynamicShaderCode[shaderCode.size()] = '\0';

	return dynamicShaderCode;
}

unsigned int Shader::createShaderProgram(const char* shaderFilePath,int shaderType) {
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

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	unsigned int vertexShader = createShaderProgram(vertexPath, GL_VERTEX_SHADER);
	unsigned int fragmentShader = createShaderProgram(fragmentPath, GL_FRAGMENT_SHADER);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec4f(const std::string& name, float x, float y, float z, float w) const {
	glUniform4f(
	glGetUniformLocation(ID, name.c_str()),
		x,
		y,
		z,
		w
	);
}