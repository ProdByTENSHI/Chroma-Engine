#include "rendering/Shader.h"

#include <fstream>
#include <iostream>

namespace chroma
{
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) : m_Program(0)
	{
		// Create Shader
		GLuint _vertexShader = CreateShader(vertexPath, GL_VERTEX_SHADER);
		GLuint _fragmentShader = CreateShader(fragmentPath, GL_FRAGMENT_SHADER);

		// Compile Shader
		CompileShader(_vertexShader);
		CompileShader(_fragmentShader);

		// Create Shader Program
		GLuint _program = 0;
		glAttachShader(_program, _vertexShader);
		glAttachShader(_program, _fragmentShader);

		glLinkProgram(_program);

		m_Program = _program;

		// Check for Linking Errors
		GLint _linkStatus = 0;
		glGetProgramiv(_program, GL_LINK_STATUS, &_linkStatus);
		if (_linkStatus != GL_TRUE)
		{
			GLsizei _logLength;
			GLchar _logMessage[1024];
			glGetProgramInfoLog(_program, 1024, &_logLength, _logMessage);
		}

		// Cleam up
		glDeleteShader(_vertexShader);
		glDeleteShader(_fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_Program);
	}

	GLuint Shader::CreateShader(const std::string& path, GLenum type)
	{
		if (type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER)
		{
			std::cerr << "Invalid type for creating Shader from Path " << path << std::endl;
			return 0;
		}

		int _shader = glCreateShader(type);

		return _shader;
	}

	void Shader::CompileShader(GLuint shader)
	{
		glCompileShader(shader);

		// Check for compilation errors
		GLint _compilationStatus;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &_compilationStatus);
		if (_compilationStatus != GLEW_OK)
		{
			GLsizei _logLength = 0;
			GLchar _logMessage[1024];

			glGetShaderInfoLog(shader, 1024, &_logLength, _logMessage);
			std::cerr << "Error Compiling Shader. Error: " << _logMessage << std::endl;
		}
	}

	void Shader::Use()
	{
	}

	std::string Shader::GetSourceFromFile(const std::string& path)
	{
		std::string _source;
		std::ifstream _stream(path);

		if (!_stream.is_open())
		{
			std::cerr << "Could not open Shader File " << path << std::endl;
			return _source;
		}

		while (getline(_stream, _source))
		{
			std::cout << _source << std::endl;
		}

		_stream.close();

		return _source;
	}
}