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
Model::Model(std::string const& path, bool gamma) : gammaCorrection(gamma)
{
	loadModel(path);
}


/**
*
*/
void Model::loadModel(std::string path)
{
	// assimp has ownership of the pointer so it will delete the resource once
	// it's destructor is invoked once this function loadModel(...) is out of scope.
	// Using assimp postprocessing for speed optimizations.
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

Mesh Model::processMesh(aiMesh* mesh, aiScene const* scene)
{
	
}