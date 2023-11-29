#include <glad/glad.h>
#include "triangle.h"
#include "shader-util.h"

// �ʱ� -1�� ����.
unsigned int TRIANGLE_SHADER_PROGRAM = -1;

unsigned int indices[] = {
	0,1,3,
	1,2,3
};

Triangle::Triangle(float vertices[], int size) {
	if (TRIANGLE_SHADER_PROGRAM == -1) {
		unsigned int vertexShader = createShaderProgram("./triangle-vertex-shader.glsl", GL_VERTEX_SHADER);
		unsigned int fragmentShader = createShaderProgram("./triangle-fragment-shader.glsl", GL_FRAGMENT_SHADER);

		TRIANGLE_SHADER_PROGRAM = glCreateProgram();
		std::cout << TRIANGLE_SHADER_PROGRAM << std::endl;
		glAttachShader(TRIANGLE_SHADER_PROGRAM, vertexShader);
		glAttachShader(TRIANGLE_SHADER_PROGRAM, fragmentShader);
		glLinkProgram(TRIANGLE_SHADER_PROGRAM);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		int success;
		char infoLog[512];
		glGetProgramiv(TRIANGLE_SHADER_PROGRAM, GL_LINK_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}
	this->vertices = new float[size];
	std::copy(vertices, vertices + size, this->vertices);


	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	this->VAO = VAO;
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	this->VBO = VBO;


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), this->vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	// EBO Bind
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	this->EBO = EBO;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);




	// VAO unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Triangle::render() {
	glUseProgram(TRIANGLE_SHADER_PROGRAM);
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Triangle::~Triangle() {
	delete[] this->vertices;
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}