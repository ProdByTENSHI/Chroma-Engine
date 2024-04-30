#pragma once

#include <string>
#include <GL/glew.h>

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

	private:
		GLuint m_Program;

		//! Tries reading the Source code of the given Shader File
		std::string GetSourceFromFile(const std::string& path);
	};
}