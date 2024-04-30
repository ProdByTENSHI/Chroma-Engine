#include "rendering/VAO.h"

namespace chroma
{
	VAO::VAO() : m_BufferID(0)
	{
		glGenVertexArrays(1, &m_BufferID);
	}

	VAO::~VAO()
	{
		glDeleteVertexArrays(1, &m_BufferID);
	}

	void VAO::Bind()
	{
		glBindVertexArray(m_BufferID);
	}

	void VAO::Unbind()
	{
		glBindVertexArray(0);
	}

	void VAO::PushVertexAttrib(const VAOLayout& layout)
	{
		glEnableVertexAttribArray(layout.attribIndex);
		glVertexAttribPointer(layout.attribIndex, layout.size, layout.type, layout.shouldNormalize, layout.stride, layout.pointer);
	}

	void VAO::PopVertexAttrib(GLint index)
	{
		glDisableVertexAttribArray(index);
	}
}