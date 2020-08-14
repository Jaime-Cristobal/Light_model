#include <algorithm>

#include "Mesh.h"
using lmt::Mesh;
using lmt::Texture;
using lmt::Vertex;
// #include "Shader.h"
using lmt::Shader;

// #include <vector>
using std::vector;
// #include <string>
using std::string;


/*
* 
*/
Mesh::Mesh(vector<Vertex> vert, vector<unsigned int> ind, vector<Texture> tex)
	: vertices(vert), indices(ind), textures(tex) 
{
	setupMesh();
}


/*
*
*/
void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// store vertex attributes to array
	glBindVertexArray(VAO);
	
	// load vertices/vector data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// load triangle face indices into element buffers to reduce duplicated vertex
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	// vertex texture coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, bitangent)));

	glBindVertexArray(0);
}


/*
*
*/
void Mesh::draw(Shader& shader)
{
	// Types to be binded to the shader for lighting effects
	// These variables refer to the amount of each lighting source type used per texture
	// ex. amount of diffuse, specular, etc.
	unsigned int diffuseAmnt{ 1 };
	unsigned int specularAmnt{ 1 };
	unsigned int normalAmnt = 1;
	unsigned int heightAmnt = 1;

	for_each(begin(textures), end(textures), 
		[&, idx = 0](auto tex) mutable 
		{ 
			glActiveTexture(GL_TEXTURE0 + idx);

			// retrieve texture number
			string number;
			string name = tex.type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseAmnt++);			// transfer unsigned int to stream
			else if (name == "texture_specular")
				number = std::to_string(specularAmnt++);
			else if (name == "texture_normal")
				number = std::to_string(normalAmnt++);
			else if (name == "texture_height")
				number = std::to_string(heightAmnt++);

			shader.setInt((name + number).c_str(), idx);
			glBindTexture(GL_TEXTURE_2D, tex.id);

			idx++;
		}
	);

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// set back to default
	glActiveTexture(GL_TEXTURE0);
}