#pragma once

#include "DestroyGLFW.h"

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <memory>

#include "Camera.h"
#include "Shader.h"
#include "Model.h"
#include "LightSource.h"


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
		void processInput();

	public:
		Launcher(unsigned int width=800, unsigned int height=600, std::string const& title= "OpenGL Proj");
		void run();

		/**
		* C callback functions for GLFW.
		*/
		void frameBufferSizeCallback(GLFWwindow* win, int width, int height);
		void mouseCallBack(GLFWwindow* win, double xPos, double yPos);
		void scrollCallBack(GLFWwindow* win, double xOffset, double yOffset);
	};
}