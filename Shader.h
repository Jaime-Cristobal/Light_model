#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

namespace lmt
{
	class Shader
	{
	private:
		GLuint id;
	public:
		Shader(std::string const& vertexPath, std::string const& fragmentPath);
		void use();
		void setBool(std::string const& name, bool value) const;
		void setInt(std::string const& name, int value) const;
		void setFloat(std::string const& name, float value) const;
		void setColor(std::string const& name, float red, float green,
			float blue, float alpha) const;
		void setVec3(std::string const& name, glm::vec3 const& value) const;
		void setVec3(std::string const& name, float x, float y, float z) const;
		void setMat4(std::string const& name, glm::mat4 const& matrix) const;
	};
}