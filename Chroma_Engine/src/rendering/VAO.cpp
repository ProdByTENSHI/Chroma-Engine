#include "rendering/VAO.h"

namespace chroma
{
	VAO::VAO() : m_ID(0)
	{
		glGenVertexArrays(1, &m_ID);
	}

	VAO::~VAO()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	void VAO::Bind()
	{
		glBindVertexArray(m_ID);
	}

	void VAO::Unbind()
	{
		glBindVertexArray(0);
	}

	void VAO::EnableVertexAttrib(const VAOLayout& layout)
	{
		glEnableVertexAttribArray(layout.attribIndex);
		glVertexAttribPointer(layout.attribIndex, layout.size, layout.type, layout.shouldNormalize, layout.stride, layout.pointer);
	}

	void VAO::DisableVertexAttrib(GLint index)
	{
		glDisableVertexAttribArray(index);
	}
}