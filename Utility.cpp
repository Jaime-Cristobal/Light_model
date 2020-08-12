#include "Utility.h"


/**
* 
*/
unsigned int lmt::loadTexture(std::string path, std::string const& directory, bool gamma)
{
	auto file{ directory + '/' + path };
	unsigned int textureID;

	glGenTextures(1, &textureID);

	int width, height, componentAmnt;
	auto* data = stbi_load(file.c_str(), &width, &height, &componentAmnt, 0);

	if (data)
	{
		GLenum format;
		switch (componentAmnt)
		{
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			break;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
		std::cout << "Texture failed to load at path: " << path << std::endl;

	stbi_image_free(data);

	return textureID;
}