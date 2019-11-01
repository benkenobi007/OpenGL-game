#pragma once

#include<glew.h>
#include<glfw3.h>

#include<vector>
#include "Vertex.h"

class Primitive {
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
public:
	Primitive() {}
	virtual ~Primitive() {}

	//Functions
	void set(const Vertex* vertices,
		const unsigned nrOfVertices,
		const GLuint* indices,
		const unsigned nrOfIndices) 
	{
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertices.push_back(vertices[i]);
		}

		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indices.push_back(indices[i]);
		}

	}

	inline Vertex* getVertices() { return this->vertices.data(); }
	inline GLuint* getIndices() { return this->indices.data(); }
	const unsigned getNrOfVertices() { return this->vertices.size(); }
	const unsigned getNrOfIndices() { return this->indices.size(); }
};

class Triangle : public Primitive
{
public:
	Triangle()
		:Primitive()
	{
		Vertex vertices[] = {
			//POSITION							//COLOR						//TEXCOORD				//NORMAL
			glm::vec3(-0.5f, 0.5f, 0.f),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,	//Triangle 1
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Quad : public Primitive
{
public:
	Quad()
		:Primitive()
	{
		Vertex vertices[] = {
			//POSITION							//COLOR						//TEXCOORD				//NORMAL
			glm::vec3(-0.5f, 0.5f, 0.f),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.f),			glm::vec3(0.f, 1.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),


		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,	//Triangle 1
			0, 2, 3,	//Triangle 2
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Pyramid : public Primitive
{
public:
	Pyramid()
		:Primitive()
	{
		Vertex vertices[] = {
			//POSITION							//COLOR						//TEXCOORD				//NORMAL
			//TRIANGLE FRONT
			glm::vec3(0.f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.5f, 1.f),	glm::vec3(0.f, 1.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 1.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 1.f, 1.f),
			
			//TRIANGLE LEFT
			glm::vec3(0.f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.5f, 1.f),	glm::vec3(-1.f, 1.f, 0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(-1.f, 1.f, 0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(-1.f, 1.f, 0.f),

			//TRIANGLE BACK
			glm::vec3(0.f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.5f, 1.f),	glm::vec3(0.f, 1.f, -1.f),
			glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 1.f, -1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 1.f, -1.f),

			//TRIANGLE RIGHT
			glm::vec3(0.f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.5f, 1.f),	glm::vec3(1.f, 1.f, 0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(1.f, 1.f, 0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),	glm::vec3(1.f, 1.f, 0.f),

		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		this->set(vertices, nrOfVertices, nullptr, 0);
	}
};

class Cube : public Primitive {
public:
	Cube(float len = 2)
		:Primitive()
	{
		float coord = 0.5f * len;
		Vertex vertices[] = {
			//POSITION										//COLOR						//TEXCOORD				//NORMAL
			//FRONT
			glm::vec3(-coord, coord, coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-coord, -coord, coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(coord, -coord, coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(coord, coord, coord),					glm::vec3(1.f, 0.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),
			
			
			//LEFT
			glm::vec3(-coord, coord, -coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-coord, -coord, -coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-coord, -coord, coord),				glm::vec3(1.f, 0.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-coord, coord, coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(-1.f, 0.f, 0.f),

			//BACK
			glm::vec3(-coord, coord, -coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-coord, -coord, -coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(coord, -coord, -coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(coord, coord, -coord),				glm::vec3(1.f, 0.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, -1.f),

			//RIGHT
			glm::vec3(coord, coord, -coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(coord, -coord, -coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(coord, -coord, coord),				glm::vec3(1.f, 0.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(coord, coord, coord),			        glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(1.f, 0.f, 0.f),

			//TOP
			glm::vec3(-coord, coord, -coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 1.f, 1.f),
			glm::vec3(-coord, coord, coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(coord, coord, coord),					glm::vec3(1.f, 0.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(coord, coord, -coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 1.f, 0.f),

			//BOTTOM
			glm::vec3(-coord, -coord, -coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, -1.f, 1.f),
			glm::vec3(-coord, -coord, coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, -1.f, 0.f),
			glm::vec3(coord, -coord, coord),				glm::vec3(1.f, 0.f, 0.f),	glm::vec2(1.f, 1.f),	glm::vec3(0.f, -1.f, 0.f),
			glm::vec3(coord, -coord, -coord),			    glm::vec3(0.5f, 0.5f, 0.f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, -1.f, 0.f),


		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] = {
			//front
			0,1,2,
			0,2,3,

			//left
			4,5,6,
			4,6,7,

			//back
			8,9,10,
			8,10,11,

			//right
			12,13,14,
			12,14,15,

			//top
			16, 17, 18,
			16, 18, 19,

			//bottom
			20, 21, 22,
			20, 22, 23,

		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Ground : public Primitive
{
private:
public:
	Ground(float height = 0.f, float x_extent = 1000.f, float z_extent=1000.f)
		:Primitive()
	{
		Vertex vertices[] = {
			//POSITION									//COLOR						//TEXCOORD				//NORMAL
			glm::vec3(-x_extent, height, z_extent),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1000.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-x_extent, height, -z_extent),	glm::vec3(0.f, 1.f, 0.f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(x_extent, height, -z_extent),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1000.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(x_extent, height, z_extent),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(1000.f, 1000.f),	glm::vec3(0.f, 0.f, 1.f),

		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,	//Triangle 1
			0, 2, 3,	//Triangle 2
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};