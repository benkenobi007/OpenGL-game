#pragma once

#include<iostream>
#include<vector>

#include "Vertex.h"
#include "shader.h"
#include "Texture.h"
#include "Material.h"

class Mesh {
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 modelMatrix;

	void initVertexData(Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndices)
	{
		for (size_t i = 0; i < nrOfVertices; i++) {
			this->vertices.push_back(vertexArray[i]);
		}

		for (size_t i = 0; i < nrOfIndices; i++) {
			this->indices.push_back(indexArray[i]);
		}
	}

	void initVAO() 
	{
		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO BIND AND SEND DATA
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);

		//GEN EBO BIND AND SEND DATA
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size()*sizeof(GLuint), this->indices.data(), GL_STATIC_DRAW);

		//SET VERTEXATTRIBDATA AND ENABLE (INPUT ASSEMBLY)
		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		//Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		//Texcoord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);
		//Normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		//Unbind VAO
		glBindVertexArray(0);
	}

	void initModelMatrix()
	{
		this->position = glm::vec3(0.f);
		this->rotation = glm::vec3(0.f);
		this->scale = glm::vec3(1.f);

		this->modelMatrix = glm::mat4(1.f);
		this->modelMatrix = glm::translate(this->modelMatrix, this->position);
		this->modelMatrix = glm::rotate(this->modelMatrix, this->rotation.x, glm::vec3(1.f, 0.f, 0.f));
		this->modelMatrix = glm::rotate(this->modelMatrix, this->rotation.y, glm::vec3(0.f, 1.f, 0.f));
		this->modelMatrix = glm::rotate(this->modelMatrix, this->rotation.z, glm::vec3(0.f, 0.f, 1.f));
		this->modelMatrix = glm::scale(this->modelMatrix, this->scale);
	}

	void updateUniforms(Shader* shader) 
	{
		shader->setMat4fv(this->modelMatrix, "modelMatrix");
	}

public:
	Mesh(Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndices)
	{
		this->initVertexData(vertexArray, nrOfVertices, indexArray, nrOfIndices);
		this->initVAO();
		this->initModelMatrix();
	}

	~Mesh()
	{
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);
	}

	void update();
	void render(Shader* shader)
	{
		//Update Uniforms
		this->updateUniforms(shader);

		shader->use();

		//Bind vertex array object
		glBindVertexArray(this->VAO);

		//RENDER
		if (this->indices.empty())
			glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
		else
			glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);

		shader->unuse();
	}
};