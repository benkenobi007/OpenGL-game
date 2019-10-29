#pragma once

#include"libs.h"

//ENUMS
enum shader_enum {SHADER_CORE_PROGRAM = 0};
enum texture_enum {TEX_PIC1 = 0, TEX_PIC1_SPECULAR, TEX_PIC2, TEX_PIC2_SPECULAR};
enum material_enum {MAT_1 = 0};
enum mesh_enum{MESH_QUAD=0};


class Game
{
private:
	//VARIABLES
	//Window
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int frameBufferWidth;
	int frameBufferHeight;

	//OpenGL Context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

	//Delta Time
	float dt;
	float curTime;
	float lastTime;

	//Mouse Input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	//matrices
	//view matrix
	glm::mat4 viewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldup;
	glm::vec3 camFront;

	//projection matrix
	glm::mat4 projectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;

	//Shaders
	std::vector<Shader*> shaders;

	//Textures
	std::vector<Texture*> textures;

	//Materials
	std::vector<Material*> materials;

	//Meshes
	std::vector<Mesh*> meshes;

	//Lights
	std::vector<glm::vec3*> lights;

	//PRIVATE FUNCTIONS
	void initGLFW();
	void initWindow(const char* title, bool resizable);
	void initGLEW(); //AFTER CONTEXT CREATION !!
	void initOpenGLOptions();
	void initMatrices();
	void initShaders();
	void initTextures();
	void initMaterials();
	void initMeshes();
	void initLights();
	void initUniforms();
	
	void updateUniforms();

	//Static Variables
public:
	//Constructor and Destructor
	Game(
		const char* title,
		const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
		const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
		bool resizable);

	virtual ~Game();

	//Accessors
	int getwindowShouldClose();

	//Modifiers
	void setWindowShouldClose();

	//Functions
	void updateKeyboardInput();
	void updateMouseInput();
	void updateInput();
	void update();
	void render();
	void updateDt();

	//Static Functions
	static void framebuffer_resize_callback(GLFWwindow* window, int fbw, int fbh);
	/*static void updateInput(GLFWwindow* window);
	static void updateInput(GLFWwindow* window, Mesh& mesh);*/
};

