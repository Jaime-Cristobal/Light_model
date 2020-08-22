#include "LightSource.h"
using lmt::LightSource;

// #include <string>
using std::string;
// #include <vector>
using std::vector;


LightSource::LightSource() : position(glm::vec3(1.2f, 1.0f, 2.0f)),
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
void LightSource::addCoordinateMatrix(glm::mat4 const& matrix, string const& idName)
{
	coordinateSystems.emplace(idName, MatCoord(matrix, nullptr));
}


/**
*
*/
void LightSource::addCoordinateMatrix(glm::mat4 const& matrix, string const& idName, std::function<void(glm::mat4)> const& callback)
{
	coordinateSystems.emplace(idName, MatCoord(matrix, callback));
}


/**
* 
*/
void LightSource::draw(Shader const& shader)
{
	for_each(begin(coordinateSystems), end(coordinateSystems), [&](auto const& pair) {
		auto idName = pair.first;
		auto matrix = pair.second.matrix;
		auto callback = pair.second.callback;

		shader.setMat4(idName, matrix);

		if (callback)
			callback(matrix);
	});
}