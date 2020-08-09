#pragma once
#include <glad/glad.h>

#include <string>
#include <iostream>

#include "stb_image.h"


namespace lmt
{
	unsigned int loadTexture(std::string path, std::string const& directory, bool gamma = false);
}