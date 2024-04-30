#include "rendering/VBO.h"

namespace chroma
{
	VBO::VBO(float vertices[])
	{
		glGenBuffers(1, &m_Buffer);
		SetBufferData(vertices);
	}

	VBO::~VBO()
	{
		glDeleteBuffers(1, &m_Buffer);
	}

	void VBO::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
	}

	void VBO::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VBO::SetBufferData(float vertices[])
	{
		Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}
}