#include "rendering/IBO.h"

namespace chroma
{
	IBO::IBO() : m_BufferID(0)
	{
		glGenBuffers(1, &m_BufferID);
	}

	IBO::~IBO()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void IBO::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void IBO::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IBO::SetData(GLint indices[])
	{
		Bind();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		Unbind();
	}
}