#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <string>

#include "Mesh.h"
#include "stb_image.h"
#include "Utility.h"


namespace lmt
{
	class Model
	{
	private:
		std::vector<Texture> textures_loaded;
		std::vector<Mesh> meshes;
		std::string directory;
		bool gammaCorrection;

		void loadModel(std::string path);
		void processNode(aiNode* node, aiScene const* scene);
		Mesh processMesh(aiMesh* mesh, aiScene const* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	public:
		Model(std::string const& path, bool gamma = false);
		void draw(Shader& shader);
	};
}
