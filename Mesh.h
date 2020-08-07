/****************************************
* Mesh.h
* Date: 8/7/2020
* 
* Description: 
****************************************/

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "Shader.h"

namespace lmt
{
	/****************************************
	*
	****************************************/
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 bitangent;
		glm::vec2 texCoord;
	};

	struct Texture
	{
		unsigned int id;
		std::string type;
		std::string path;
	};


	/****************************************
	*
	****************************************/
	class Mesh
	{
	private:
		unsigned int VBO, EBO, VAO;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		void setupMesh();

	public:
		Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind, std::vector<Texture> tex);
		void draw(Shader& shader);
	};
}