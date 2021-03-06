#include "Model.h"
using lmt::Model;
// #include "Mesh.h"
using lmt::Mesh;
using lmt::Texture;
using lmt::Vertex;

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
void Model::loadModel(string const& path)
{
	// assimp has ownership of the pointer so it will delete the resource once
	// it's destructor is invoked. It's invoked once this function loadModel(...) is out of scope.
	//
	// NOTE: Using a smart pointer here will result in a segmentation fault which is fun if you're 
	//		 into that sort of thing.
	//
	// Using assimp postprocessing for speed optimizations on getting those faces.
	Assimp::Importer import;
	auto const* scene{ import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace) };

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
void Model::processNode(aiNode* node, aiScene const* scene)
{
	// Process any of the node's present meshes. There might or might not be a mesh available.
	for (unsigned int m = 0; m < node->mNumMeshes; m++)
	{
		unsigned int index = node->mMeshes[m];
		aiMesh* mesh = scene->mMeshes[index];			// scene actually contains the mesh data
		meshes.push_back(processMesh(mesh, scene));
	}

	// process node's children
	for (unsigned int c = 0; c < node->mNumChildren; c++)
	{
		processNode(node->mChildren[c], scene);
	}
}


/**
*
*/
Mesh Model::processMesh(aiMesh* mesh, aiScene const* scene)
{
	// get vertex positions, normals, tangets, bitangents, and texture coordinates (if present)
	auto vertices{ getAssimpVertexData(mesh) };

	// get the mesh indices which are the faces
	auto indices{ getAssimpMeshData(mesh) };

	// process materials needed for textures and lighting
	auto textures{ getAssimpTextureData(mesh, scene) };

	return Mesh(std::move(vertices), std::move(indices), std::move(textures));
}


/**
* 
*/
std::vector<Vertex> Model::getAssimpVertexData(aiMesh const* const mesh) const
{
	vector<Vertex> vertices;

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

	return vertices;
}


/**
*
*/
std::vector<unsigned int> Model::getAssimpMeshData(aiMesh const* const mesh) const
{
	vector<unsigned int> indices;

	for (unsigned int f = 0; f < mesh->mNumFaces; f++)
	{
		auto face{ mesh->mFaces[f] };

		// store all retrieved face incides
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return indices;
}


/**
*
*/
std::vector<Texture> Model::getAssimpTextureData(aiMesh const* const mesh, aiScene const* const scene)
{
	vector<Texture> textures;

	if (mesh->mMaterialIndex >= 0)
	{
		auto assimpMatInd{ mesh->mMaterialIndex };
		// pointer owned by assimp
		auto* material{ scene->mMaterials[assimpMatInd] };

		// NOTE: might have to change var name like "texture_diffuse" in some kind of global since that is GLSL dependant
		// diffuse maps
		auto diffuseMaps{ loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse") };
		textures.insert(end(textures), begin(diffuseMaps), end(diffuseMaps));

		// specular maps
		auto specularMaps{ loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular") };
		textures.insert(end(textures), begin(specularMaps), end(specularMaps));

		// normal maps
		auto normalMaps{ loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal") };
		textures.insert(end(textures), begin(normalMaps), end(normalMaps));

		// height maps
		auto heightMaps{ loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height") };
		textures.insert(end(textures), begin(heightMaps), end(heightMaps));
	}

	return textures;
}


/**
* 
*/
vector<Texture> Model::loadMaterialTextures(aiMaterial const* const mat, aiTextureType type, string const& typeName)
{
	vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		// check if texture was loaded before to avoid duplicates. We skip if a duplicate is found
		auto skip = false;
		find_if(begin(textures_loaded), end(textures_loaded), 
			[&](Texture loadedTex) -> bool {
				if (std::strcmp(loadedTex.path.data(), str.C_Str()) == 0)
				{
					textures.push_back(loadedTex);
					skip = true;
				}

				return skip;
			}
		);

		if (!skip)
		{
			Texture texture;
			texture.id = lmt::loadTexture(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();

			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}

	return textures;
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


/**
*
*/
void Model::draw(Shader& shader)
{
	for_each(begin(meshes), end(meshes), [&](Mesh mesh) { mesh.draw(shader); });
}