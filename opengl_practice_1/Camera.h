#pragma once

#include<iostream>

#include<glew.h>
#include<glfw3.h>

#include<glm.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

enum direction { FORWARD = 0, BACKWARD, LEFT, RIGHT };

class Camera
{
private:
	glm::mat4 viewMatrix;

	GLfloat movementSpeed;
	GLfloat sensitivity;

	glm::vec3 worldUp;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up; 

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	float Xmin;
	float Xmax;

	float Ymin;
	float Ymax;

	float Zmin;
	float Zmax;

	void updateCameraVectors()
	{
		this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->front.y = sin(glm::radians(this->pitch));
		this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

		this->front = glm::normalize(this->front);
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}

public:
	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
	{
		this->viewMatrix = glm::mat4(1.f);

		this->movementSpeed = 3.f;
		this->sensitivity = 10.f;

		this->worldUp = worldUp;
		this->position = position;
		this->right = glm::vec3(0.f);
		this->up = worldUp;

		this->pitch = 0.f;
		this->yaw = -90.f;
		this->roll = 0.f;

		this->updateCameraVectors();

	}

	//Accessors
	const glm::mat4 getViewMatrix() 
	{
		this->viewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);

		this->updateCameraVectors();

		return this->viewMatrix;
	}

	const glm::vec3 getPosition() const
	{
		return this->position;
	}

	const glm::vec3 getMinBounds()
	{
		return glm::vec3(this->Xmin, this->Ymin, this->Zmin);
	}

	//Modifiers
	void setMovementSpeed(GLfloat speed) {
		this->movementSpeed = speed;
	}

	void set_movement_bounds(float Xmin, float Xmax, float Ymin, float Ymax, float Zmin, float Zmax) 
	{
		this->Xmin = Xmin;
		this->Xmax = Xmax;

		this->Ymin = Ymin;
		this->Ymax = Ymax;

		this->Zmin = Zmin;
		this->Zmax = Zmax;

		std::cout << "Xmin : " << Xmin << "\tXmax : " << Xmax<<"\n";
		std::cout << "Ymin : " << Ymin << "\tYmax : " << Ymax << "\n";
		std::cout << "Zmin : " << Zmin << "\tZmax : " << Zmax << "\n";
		
	}

	//Functions

	//Correct position if out of bounds
	void correctPosition(glm::vec3 &position) {
		if(position.x <= this->Xmin)
			position.x = this->Xmin;
		if (position.x >= this->Xmax)
			position.x = this->Xmax;
		
		if (position.y <= this->Ymin)
			position.y = this->Ymin;
		if (position.y >= this->Ymax)
			position.y = this->Ymax;

		if (position.z <= this->Zmin)
			position.z = this->Zmin;
		if (position.z >= this->Zmax)
			position.z = this->Zmax;
		std::cout << "Position\tx : " << position.x << "\ty: " << position.y << "\tz: " << position.z << "\n";
	}

	void move(const float& dt, const int direction)
	{
		//Update position vector
		switch (direction) 
		{
		case FORWARD:
			this->position += this->front * this->movementSpeed * dt;
			break;
		case BACKWARD:
			this->position -= this->front * this->movementSpeed * dt;
			break;
		case LEFT:
			this->position -= this->right * this->movementSpeed * dt;
			break;
		case RIGHT:
			this->position += this->right * this->movementSpeed * dt;
			break;
		default:
			break;
		}

		correctPosition(this->position);
	}

	void updateMouseInput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
	{
		//Update PItch Yaw and Roll
		this->pitch += static_cast<GLfloat>(offsetY)* this->sensitivity * dt;
		this->yaw += static_cast<GLfloat>(offsetX)* this->sensitivity* dt;

		if (this->pitch > 80.f)
			this->pitch = 80.f;
		else if (this->pitch < -80.f)
			this->pitch = -80.f;

		if (this->yaw > 360.f || this->yaw < -360.f)
			this->yaw = 0.f;
	}

	void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
	{
		this->updateMouseInput(dt, direction, offsetX, offsetY);
	}
};