#include "LightSource.h"
using lmt::LightSource;

// #include <vector>
using std::vector;


LightSource::LightSource() : position(glm::vec3(1.2f, 1.0f, 2.0f)),
	view(1.0f), projection(1.0f), model(1.0f),
	vertices({		// positions				// normals        // texture coords
					-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 0.0f,
					 0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 0.0f,
					 0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
					 0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
					-0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 1.0f,
					-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 0.0f,

					-0.5f, -0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		0.0f, 0.0f,
					 0.5f, -0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		1.0f, 0.0f,
					 0.5f,  0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		1.0f, 1.0f,
					 0.5f,  0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		1.0f, 1.0f,
					-0.5f,  0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		0.0f, 1.0f,
					-0.5f, -0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		0.0f, 0.0f,

					-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
					-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
					-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
					-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
					-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
					-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,

					 0.5f,  0.5f,  0.5f,	1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
					 0.5f,  0.5f, -0.5f,	1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
					 0.5f, -0.5f, -0.5f,	1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
					 0.5f, -0.5f, -0.5f,	1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
					 0.5f, -0.5f,  0.5f,	1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
					 0.5f,  0.5f,  0.5f,	1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

					-0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 1.0f,
					 0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		1.0f, 1.0f,
					 0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
					 0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
					-0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 0.0f,
					-0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 1.0f,

					-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 1.0f,
					 0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		1.0f, 1.0f,
					 0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
					 0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
					-0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 0.0f,
					-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 1.0f 
	})
{

}


/**
* 
*/
void LightSource::setUpBuffers()
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertices.size() * sizeof(vertices), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);
}


/**
* 
*/
void LightSource::setCoordinateSystem(glm::mat4 const& view, glm::mat4 const& projection, glm::mat4 const& model)
{
	this->view = view;
	this->projection = projection;
	this->model = model;
}


/**
* 
*/
void LightSource::draw(Shader const& shader)
{
	
}