#pragma once

#include <GL/glew.h>

namespace chroma
{
	//! The Layout of a VAO
	struct VAOLayout
	{
		GLint attribIndex;
		GLint size;
		GLenum type;
		GLboolean shouldNormalize;
		GLsizei stride;
		GLvoid* pointer;
	};

	//! A VAO stores the boumd VBO Data and specifies how Shaders should interpret this Buffer Data
	class VAO
	{
	public:
		VAO();
		~VAO();

		void Bind();
		void Unbind();

		void EnableVertexAttrib(const VAOLayout& vaoLayout);
		void DisableVertexAttrib(GLint index);

		inline GLuint GetID() const { return m_ID; }

		static inline GLint GetSizeByType(GLenum type)
		{
			switch (type)
			{
			case GL_FLOAT:
				return sizeof(GLfloat);

			case GL_INT:
				return sizeof(GLint);

			case GL_BYTE:
				return sizeof(GLbyte);

			default:
				return sizeof(GLfloat);
			}
		}

	private:
		GLuint m_ID;

	};
}