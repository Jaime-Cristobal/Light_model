#include "Launcher.h"
using lmt::Launcher;
// #include "Camera.h"
using lmt::Camera;
// #include "Shader.h"
using lmt::Shader;
// #include <iostream>
using std::cout;
using std::endl;


Launcher::Launcher(unsigned int width, unsigned int height, std::string const& title) 
	: winWidth(width), winHeight(height), cam(glm::vec3(0.0f, 0.0f, 3.0f)), firstMouse(true), 
	lastX(width / 2.0f), lastY(height / 2.0f), deltaTime(0.0f), lastFrame(0.0f)
{
	// glfw: initialize and configuration
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window.reset(glfwCreateWindow(winWidth, winHeight, title.c_str(), nullptr, nullptr));

	glfwSetWindowUserPointer(window.get(), this);			// for using lambdas instead of static functions for C callbacks

	start();
}


/**
* This sets the GLFW context and callback buffer to our window pointer. If any errors
* are present, we simply output a message on the console, release the window memory,
* and return back to main.
*/
void Launcher::start() const
{
	if (!window)
	{
		cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window.get());
	glfwSetFramebufferSizeCallback(window.get(), 
		[](GLFWwindow* win, int width, int height) 
		{
			static_cast<Launcher*> (glfwGetWindowUserPointer(win))->frameBufferSizeCallback(win, width, height);
		}
	);
	glfwSetCursorPosCallback(window.get(), 
		[](GLFWwindow* win, double xPos, double yPos) 
		{
			static_cast<Launcher*> (glfwGetWindowUserPointer(win))->mouseCallBack(win, xPos, yPos);
		}
	);
	glfwSetScrollCallback(window.get(), 
		[](GLFWwindow* win, double xOffset, double yOffset) 
		{
			static_cast<Launcher*> (glfwGetWindowUserPointer(win))->scrollCallBack(win, xOffset, yOffset);
		}
	);

	glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: Load all OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return;
	}

	glEnable(GL_DEPTH_TEST);
}


void Launcher::run()
{
	Shader shaderMat("Mesh_Shader.vs", "Mesh_Shader.fs");
	Shader shaderLight("light.vs", "light.fs");

	stbi_set_flip_vertically_on_load(true);
	Model backpack("backpack/backpack.obj", 1);
	glm::mat4 projection{ glm::mat4(1.0f) };
	glm::mat4 view{ glm::mat4(1.0f) };
	glm::mat4 model{ glm::mat4(1.0f) };

	LightSource light = LightSource(glm::vec3(5.0f, 2.0f, 1.0f));
	light.addCoordinateMatrix(glm::mat4(1.0f), "projection");
	light.addCoordinateMatrix(glm::mat4(1.0f), "view");
	light.addCoordinateMatrix(glm::mat4(1.0f), "model");

	shaderMat.use();

	// set light material properties
	shaderMat.setInt("material.diffuse", 0);
	shaderMat.setInt("material.specular", 0);
	shaderMat.setFloat("material.shininess", 32.0f);

	// directional light
	shaderMat.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	shaderMat.setVec3("dirLight.ambient", 0.4f, 0.4f, 0.4f);
	shaderMat.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	shaderMat.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

	while (!glfwWindowShouldClose(window.get()))
	{
		processInput();

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// time logic per frame
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// testing backpack
		shaderMat.use();

		shaderMat.setVec3("viewPos", cam.getPosition());

		projection = glm::perspective(glm::radians(cam.getZoom()),
			static_cast<float>(winWidth / winHeight), 0.1f, 100.0f);
		shaderMat.setMat4("projection", projection);

		view = cam.getViewMatrix();
		shaderMat.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		shaderMat.setMat4("model", model);
		backpack.draw(shaderMat);

		// light box
		shaderLight.use();
		light.editCoordinateMatrix(projection, "projection");
		light.editCoordinateMatrix(view, "view");
		model = glm::mat4(1.0f);
		model = glm::translate(model, light.getPosition());
		model = glm::scale(model, glm::vec3(0.2f));
		light.editCoordinateMatrix(model, "model");
		light.draw(shaderLight);

		render();

		// buffer and callbackevents
		glfwSwapBuffers(window.get());
		glfwPollEvents();
	}

	glfwTerminate();
}


/**
*
*/
void Launcher::render() const
{

}


/**
* For C library callbacks with GLFW.
*/
void Launcher::frameBufferSizeCallback(GLFWwindow* win, int width, int height)
{
	glViewport(0, 0, width, height);
}


void Launcher::processInput()
{
	if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window.get(), true);
	
	if (glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS)
		cam.moveForward(deltaTime);
	if (glfwGetKey(window.get(), GLFW_KEY_S) == GLFW_PRESS)
		cam.moveBackward(deltaTime);
	if (glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS)
		cam.moveLeftward(deltaTime);
	if (glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS)
		cam.moveRightward(deltaTime);
}


void Launcher::mouseCallBack(GLFWwindow* win, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = static_cast<float>(xPos);
		lastY = static_cast<float>(yPos);
		firstMouse = false;
	}

	// distance between new and old positions from mouse and keyboard movements
	auto xOffset = static_cast<float>(xPos - lastX);
	auto yOffset = static_cast<float>(lastY - yPos);

	lastX = static_cast<float>(xPos);
	lastY = static_cast<float>(yPos);

	cam.processMouseMovement(xOffset, yOffset, true);
}


void Launcher::scrollCallBack(GLFWwindow* win, double xOffset, double yOffset)
{
	cam.processMouseScroll(static_cast<float>(yOffset));
}
