#include "Game.h"


//PRIVATE FUNCTIONS
void Game::initGLFW()
{
	//init glfw
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::GLFW_INIT_FAILED";
		glfwTerminate();
	}
}

void Game::initWindow(
	const char* title,
	bool resizable
)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);/// OpengGL version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);/// Major version - 4, Minor Version - 6
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, 
		"opengl_practice", NULL, NULL);

	if (this->window == nullptr)
	{
		std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
		glfwTerminate();
	}

	glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight); //for aspect ratio
	glfwSetFramebufferSizeCallback(this->window, Game::framebuffer_resize_callback);

	//glViewport(0, 0, frameBufferWidth, frameBufferHeight);
	glfwMakeContextCurrent(this->window);
}

void Game::initGLEW()
{
	//GLEW init
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR::Game.cpp::GLEW INIT FAILED" << "\n";
		glfwTerminate();
	}
}

void Game::initOpenGLOptions()
{
	//OpenGL Options
	glEnable(GL_DEPTH_TEST);

	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);*/

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initMatrices()
{
	//View Matrix
	
	this->viewMatrix = glm::mat4(1.f);
	this->viewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldup);

	//Projection Matrix
	this->projectionMatrix = glm::mat4(1.f);

	this->projectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
		this->nearPlane,
		this->farPlane
	);
}

void Game::initShaders()
{
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		(char*)"vertex_core.glsl", (char*)"fragment_core.glsl"));

}

void Game::initTextures()
{
	//TEXTURE 0
	this->textures.push_back(new Texture("Images/pic1.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/pic1_specular.png", GL_TEXTURE_2D));

	//TEXTURE 1
	this->textures.push_back(new Texture("Images/pic2.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/pic2_specular.png", GL_TEXTURE_2D));

}

void Game::initMaterials()
{
	this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f),
		0,1));

}

void Game::initMeshes()
{
	this->meshes.push_back(
		new Mesh(&Pyramid(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);

}

void Game::initModels()
{
	this->models.push_back(new Model(
		glm::vec3(0.f),
		this->materials[0],
		this->textures[TEX_PIC1],
		this->textures[TEX_PIC2],
		this->meshes
	)
	);
}

void Game::initLights()
{
	this->lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}

void Game::initUniforms()
{
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->viewMatrix, "viewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->projectionMatrix, "projectionMatrix");

	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
	
}

void Game::updateUniforms()
{
	//Update framebuffer size
	glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);

	//this->viewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldup);
	this->viewMatrix = this->camera.getViewMatrix();
	this->camPosition = this->camera.getPosition();

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->viewMatrix, "viewMatrix");

	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "camPosition");

	this->projectionMatrix = glm::perspective(
		glm::radians(fov),
		static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
		this->nearPlane,
		this->farPlane
	);
	
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->projectionMatrix, "projectionMatrix");

}

//CONSTRUCTOR
Game::Game(
	const char* title,
	const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
	const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
	bool resizable
)
	: WINDOW_WIDTH(WINDOW_WIDTH),
	WINDOW_HEIGHT(WINDOW_HEIGHT),
	GL_VERSION_MAJOR(GL_VERSION_MAJOR),
	GL_VERSION_MINOR(GL_VERSION_MINOR),
	camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
{
	//Camera cam();

	//init variables
	this->window = nullptr;
	this->frameBufferWidth = this->WINDOW_WIDTH;
	this->frameBufferHeight = this->WINDOW_HEIGHT;

	this->dt = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;

	this->lastMouseX = 0.0;
	this->lastMouseY = 0.0;
	this->mouseX = 0.0;
	this->mouseY = 0.0;
	this->mouseOffsetX = 0.0;
	this->mouseOffsetY = 0.0;
	this->firstMouse = true;

	this->initGLFW();
	this->initWindow(title, resizable);
	this->initGLEW();
	this->initOpenGLOptions();

	//Initialize Matrices
	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldup = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);
	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initMeshes();
	this->initModels();
	this->initLights();
	this->initUniforms();

}

//DESTRUCTOR
Game::~Game() 
{
	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (size_t i = 0; i < this->shaders.size(); i++)
		delete this->shaders[i];

	for (size_t i = 0; i < this->textures.size(); i++)
		delete this->textures[i];

	for (size_t i = 0; i < this->materials.size(); i++)
		delete this->materials[i];

	for (size_t i = 0; i < this->meshes.size(); i++)
		delete this->meshes[i];

	for (auto*& i : this->models)
		delete i;

	for (size_t i = 0; i < this->lights.size(); i++)
		delete this->lights[i];
}

//Accessors
int Game::getwindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

//Modifiers
void Game::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

//FUNCTIONS
void Game::update()
{
	//Update Input
	this->updateDt();
	this->updateInput();
	this->camera.updateInput(this->dt, -1, this->mouseOffsetX, this->mouseOffsetY);
	//this->meshes[MESH_QUAD]->rotate(glm::vec3(0.001f, 0.f, 0.f));

	/*if (this->mouseOffsetX != 0 || this->mouseOffsetY != 0)
		std::cout << "DT : " << this->dt << "\n"
		<< "Mouse OffsetX: " << this->mouseOffsetX << "\n"
		<< "Mouse OffsetY: " << this->mouseOffsetY << "\n";*/
}

void Game::render()
{

	//update
	//this->update();
	this->update();

	//clear
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Update uniforms
	this->updateUniforms();
	
	//update models
	this->models[0]->render(this->shaders[SHADER_CORE_PROGRAM]);

	//End draw
	glfwSwapBuffers(window);
	glFlush();

	//Reset
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::updateDt()
{
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;
}

void Game::updateKeyboardInput()
{
	//EXIT
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		this->setWindowShouldClose();
	}

	//CAMERA
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) {
		//this->camPosition.z -= 0.005f;
		this->camera.move(this->dt, FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) {
		//this->camPosition.z += 0.01f;
		this->camera.move(this->dt, BACKWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) {
		//this->camPosition.x -= 0.01f;
		this->camera.move(this->dt, LEFT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) {
		//this->camPosition.x += 0.01f;
		this->camera.move(this->dt, RIGHT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS) {
		this->camPosition.y += 0.01f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		this->camPosition.y -= 0.01f;
	}

}

void Game::updateMouseInput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse)
	{
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	//Calculate Offset
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY; //Y is inverted

	//Update lastMouse
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;
}

void Game::updateInput()
{
	glfwPollEvents();
	this->updateKeyboardInput();
	this->updateMouseInput();

}

//STATIC FUNCTIONS
void Game::framebuffer_resize_callback(GLFWwindow* window, int fbw, int fbh)
{
	glViewport(0, 0, fbw, fbh);
}

/*
void Game::updateInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void Game::updateInput(GLFWwindow* window, Mesh& mesh) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		mesh.move(glm::vec3(0.f, 0.f, -0.001f));
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		mesh.move(glm::vec3(0.f, 0.f, 0.001f));
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		mesh.move(glm::vec3(-0.001f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		mesh.move(glm::vec3(0.001f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		mesh.move(glm::vec3(0.f, 0.001f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		mesh.move(glm::vec3(0.f, -0.001f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		mesh.rotate(glm::vec3(0.f, -0.001f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		mesh.rotate(glm::vec3(0.f, 0.001f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		mesh.updateScale(glm::vec3(1.f));
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		mesh.updateScale(glm::vec3(-1.f));
	}
}
*/