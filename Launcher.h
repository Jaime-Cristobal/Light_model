#pragma once

#include <glad/glad.h>
#include <string>
#include <memory>

#include "DestroyGLFW.h"
#include "Camera.h"


namespace lmt 
{
	class Launcher
	{
	private:
		typedef std::unique_ptr<GLFWwindow, DestroyGLFW> SmartGLFWwindow;
		SmartGLFWwindow window;
		unsigned int const winWidth;
		unsigned int const winHeight;

		// for camera movements
		lmt::Camera cam;
		bool firstMouse;
		float lastX;
		float lastY;

		// rendering purposes
		float deltaTime;
		float lastFrame;

		void start() const;
		void render() const;

	public:
		Launcher(unsigned int width=800, unsigned int height=600, std::string const& title= "OpenGL Proj");
		void run() const;
	};


	/**
	* FREE FUNCTIONS
	* C callback functions for GLFW.
	*/
	void frameBufferSizeCallback(GLFWwindow* win, int const width, int const height);
	void processInput(GLFWwindow* win);
	void mouseCallBack(GLFWwindow* win, Camera& cam, bool& firstMouse, float& lastX, float& lastY, float xPos, float yPos);
	void scrollCallBack(GLFWwindow* win, Camera& cam, float yOffset);
}