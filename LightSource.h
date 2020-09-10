#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>

#include "Shader.h"


namespace lmt
{
	struct MatCoord
	{
		glm::mat4 matrix;
		std::function<void(glm::mat4)> callback;
		
		MatCoord() : matrix(1.0f), callback(nullptr) {}
		MatCoord(glm::mat4 mat) : matrix(mat), callback(nullptr) {}
		MatCoord(glm::mat4 mat, std::function<void(glm::mat4)> const& func) : matrix(mat), callback(func) {}
	};


	class LightSource
	{
	private:
		unsigned int VBO;
		unsigned int VAO;
		glm::vec3 position;
		std::vector<float> vertices;		// temporary cube placeholder
		std::unordered_map<std::string, MatCoord> coordinateSystems;

		void setUpBuffers();

	public:
		LightSource(glm::vec3 pos = glm::vec3(1.2f, 1.0f, 2.0f));
		~LightSource();
		void addCoordinateMatrix(glm::mat4 const& matrix, std::string const& idName);
		void addCoordinateMatrix(glm::mat4 const& matrix, std::string const& idName, std::function<void(glm::mat4)> const& callback);
		void editCoordinateMatrix(glm::mat4 const& matrix, std::string const& idName);
		void draw(Shader const& shader);
		glm::vec3 getPosition() const;
	};
}