#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <initializer_list>
#include <functional>

#include "Shader.h"


namespace lmt
{
	class LightSource
	{
	private:
		typedef std::function<void()> FuncCallbacks;

		unsigned int VBO;
		unsigned int VAO;
		glm::vec3 position;
		std::vector<float> vertices;		// temporary cube placeholder
		std::unordered_map<std::string, glm::mat4> coordinateSystems;

		void setUpBuffers();
		void addCoordinateMatrix(glm::mat4 const& matrix, std::string const& idName);

	public:
		LightSource();
		void draw(Shader const& shader);
		void draw(Shader const& shader, std::initializer_list<FuncCallbacks> callbackList);
	};
}