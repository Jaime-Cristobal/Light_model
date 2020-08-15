#include "Launcher.h"
using lmt::Launcher;
// #include "Camera.h"
using lmt::Camera;
#include "Shader.h"
#include <iostream>
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
	glfwSetFramebufferSizeCallback(window.get(), frameBufferSizeCallback);
	glfwSetCursorPosCallback(window.get(), mouseCallBack);
	glfwSetScrollCallback(window.get(), scrollCallBack);

	// glad: Load all OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return;
	}

	glEnable(GL_DEPTH_TEST);
}


void Launcher::run() const
{
	lmt::Shader shader("material.vs", "Multiple_light.fs");

	while (!glfwWindowShouldClose(window.get()))
	{
		processInput(window.get());

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window.get());
		glfwPollEvents();

		render();
	}
}


void Launcher::render() const
{

}

/**
* FREE FUNCTIONS
* For C library constraints with GLFW.
*/
void lmt::frameBufferSizeCallback(GLFWwindow* win, int const width, int const height)
{
	glViewport(0, 0, width, height);
}


void lmt::processInput(GLFWwindow* win)
{
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(win, true);
}


void lmt::mouseCallBack(GLFWwindow* win, Camera& cam, bool& firstMouse, float& lastX, float& lastY, float xPos, float yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	// distance between new and old positions from mouse and keyboard movements
	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	cam.processMouseMovement(xOffset, yOffset, true);
}


void lmt::scrollCallBack(GLFWwindow* win, Camera& cam, float yOffset)
{
	cam.processMouseScroll(yOffset);
}
