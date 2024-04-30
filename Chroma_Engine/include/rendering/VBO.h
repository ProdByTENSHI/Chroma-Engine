#pragma once

#include <GL/glew.h>

namespace chroma
{
	class VBO
	{
	public:
		VBO();
		~VBO();

		void Bind();
		void Unbind();
		void SetBufferData(float vertices[]);

	private:
		GLuint m_Buffer;

	};
}