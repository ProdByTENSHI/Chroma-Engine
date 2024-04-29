#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

namespace chroma
{
	class VBO
	{
	public:
		VBO(float vertices[]);
		~VBO();

		void Bind();
		void Unbind();

	private:
		GLuint m_Buffer;

	};
}