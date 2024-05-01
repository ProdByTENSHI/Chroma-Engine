#pragma once

#include <string>
#include <GL/glew.h>
#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace chroma
{
	class Shader
	{
	public:
		//! Create Shader Program from Vertex and Fragment Shader
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		//! Creates the Shader and loads its Source from the Path
		//! \arg \c path[in] The File Path for the Shader
		//! \arg \c type[in] Shader Type. See GLenum for Shader Types
		GLuint CreateShader(const std::string& path, GLenum type);

		void CompileShader(GLuint shader);

		//! Use this Shader
		void Use();

		//! Returns the Shader Program ID
		inline GLuint GetProgram() { return m_Program; }

		// -- Utlity Functions for passing Data Shader
		//! Set given Uniform Integer
		void SetUniform1i(const std::string& name, GLint value);

		//! Set  given Uniform Float
		void SetUniform1f(const std::string& name, GLfloat value);

		//! Set given Uniform Vector2
		void SetUniformVec2f(const std::string& name, const glm::vec2& value);

		//! Set given Uniform Vector3
		void SetUniformVec3f(const std::string& name, const glm::vec3& value);

		//! Returns the Location of a Uniform
		GLint GetUniformLocation(const std::string& name);

	private:
		//! The Program ID
		GLuint m_Program;

		//! Cache for the Uniform Locations to reduce OpenGL Calls
		std::unordered_map<std::string, GLint> m_UniformCache;

		//! Tries reading the Source code of the given Shader File
		std::string GetSourceFromFile(const std::string& path);
	};
}