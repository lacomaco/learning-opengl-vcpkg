#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "triangle.h"
#include "shader.h"

unsigned int indices[] = {
	0,1,2
};

Triangle::Triangle(float vertices[], int size, Shader* shader) {
	this->shader = shader;

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

	// vertex attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	// color attribute pointer
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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
	this->shader->use();
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Triangle::~Triangle() {
	delete[] this->vertices;
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}