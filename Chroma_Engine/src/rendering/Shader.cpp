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
		glUseProgram(m_Program);
	}

	void Shader::SetUniform1i(const std::string& name, GLint value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1f(const std::string& name, GLfloat value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniformVec2f(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void Shader::SetUniformVec3f(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	GLint Shader::GetUniformLocation(const std::string& name)
	{
		// Try to load from cache
		if (m_UniformCache.find(name) != m_UniformCache.end())
			return m_UniformCache[name];

		// Try to get Uniform Location
		GLint _location = glGetUniformLocation(m_Program, name.c_str());

		// Check for Errors
		if (_location == -1)
		{
			std::cerr << "WARNING: Uniform Location " << name << " does not exist!" << std::endl;

			GLint _activeUniformsCount;
			glGetProgramiv(m_Program, GL_ACTIVE_UNIFORMS, &_activeUniformsCount);
			for (int i = 0; _activeUniformsCount < 0; i++)
			{
				char _name[100];
				glGetActiveUniformName(m_Program, i, sizeof(_name), nullptr, _name);
				std::cout << "Active Uniforms: " << _name << std::endl;
			}
		}
		else
		{
			m_UniformCache.insert({ name, _location });
		}

		return _location;
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