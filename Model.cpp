#include "Model.h"
using lmt::Model;
// #include "Mesh.h"
using lmt::Mesh;

// #include <iostream>
using std::cout;
using std::endl;
// #include <string>
using std::string;
// #include <vector>
using std::vector;


/**
*
*/
Model::Model(string const& path, int texCoordAmnt, bool gamma) : gammaCorrection(gamma), texCoordAmnt(texCoordAmnt)
{
	if (this->texCoordAmnt <= 0)
	{
		cout << "WARNING::MODEL_H::LMT::MODEL. Variable texCoordAmnt cannot be less than 1! Value is now defaulted to 1" << endl;
		texCoordAmnt = 1;
	}

	loadModel(path);
}


/**
*
*/
void Model::loadModel(string path)
{
	// assimp has ownership of the pointer so it will delete the resource once
	// it's destructor is invoked. It's invoked once this function loadModel(...) is out of scope.
	//
	// NOTE: Using a smart pointer here will result in a segmentation fault which is fun if you're 
	//		 into that sort of thing.
	//
	// Using assimp postprocessing for speed optimizations on getting those faces.
	Assimp::Importer import;
	aiScene const* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
	}

	directory = path.substr(0, path.find_last_of('/'));

	// assimp's root node consist of it's children and meshes.
	// All the child nodes in the root node will be recursively processed like a graph. 
	processNode(scene->mRootNode, scene);
}


/**
*
*/
Mesh Model::processMesh(aiMesh* mesh, aiScene const* scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	// get vertex positions, normals, tangets, bitangents, and texture coordinates (if present)
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		
		vertex.position = get3DVectorAttr(mesh->mVertices[i]);
		vertex.normal = get3DVectorAttr(mesh->mNormals[i]);
		vertex.tangent = get3DVectorAttr(mesh->mTangents[i]);
		vertex.bitangent = get3DVectorAttr(mesh->mBitangents[i]);

		// Unlike vertex position and normal, we have to test if texture coordinates are present
		// in the mesh as it does not always contain one.
		for (int texSet = 0; texSet < texCoordAmnt; texSet++)
		{
			if (mesh->mTextureCoords[texSet])
				vertex.texCoord = get2DVectorAttr(mesh->mTextureCoords[texSet][i]);
			else
				vertex.texCoord = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	// Get the indices which are the faces
	for (aiFace const& face : mesh->mFaces)		// NOTE: mFaces is a pointer, NOT AN ARRAY
	{											// Note to self: try old school for loops using mNumFaces
												// next time.
	}
}


/**
*
*/
glm::vec3 lmt::get3DVectorAttr(aiVector3D const& vec)
{
	glm::vec3 vector;
	vector.x = vec.x;
	vector.y = vec.y;
	vector.z = vec.z;

	return vector;
}


/**
* Yes this says get 2D vector attributes but takes a 3D vector. 
*/
glm::vec2 lmt::get2DVectorAttr(aiVector3D const& vec)
{
	glm::vec2 vector;
	vector.x = vec.x;
	vector.y = vec.y;

	return vector;
}
