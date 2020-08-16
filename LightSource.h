#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "Shader.h"


namespace lmt
{
	class LightSource
	{
	private:
		unsigned int VBO;
		unsigned int VAO;
		glm::vec3 position;
		std::vector<float> vertices;		// temporary cube placeholder
		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 model;

		void setUpBuffers();
		void setCoordinateSystem(glm::mat4 const& view, glm::mat4 const& projection, glm::mat4 const& model);

	public:
		LightSource();
		void draw(Shader const& shader);
	};
}