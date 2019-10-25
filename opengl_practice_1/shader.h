#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#include<glew.h>
#include<glfw3.h>

#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

class Shader {
private:
	//Member variables
	GLuint id;

	//Private Functions
	std::string loadShaderSource(char* fileName) {
		std::string temp = "";
		std::string src = "";

		std::ifstream in_file;

		//Vertex Shader
		in_file.open(fileName);

		if (in_file.is_open()) {
			while (std::getline(in_file, temp))
				src += temp + "\n";
		}
		else {
			std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE" << fileName << "\n";
		}
		in_file.close();
		return src;
	}

	GLuint loadShader(GLenum type, char* filename) {
		bool loadSuccess = true;
		char infoLog[512];
		GLint success;

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* vertSrc = src.c_str();
		glShaderSource(vertexShader, 1, &vertSrc, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_VERTEX_SHADER" << "\n";
			std::cout << infoLog << "\n";
			loadSuccess = false;
		}
	}

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader) {

	}

public:
	Shader(char* vertexFile, char* fragmentFile, char* geometryFile = (char*)"") {

	}

	~Shader() {
		glDeleteProgram(this->id);
	}

	//Set uniform functions
};