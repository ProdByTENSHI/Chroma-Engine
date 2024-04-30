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
		//! Generated the Vertex Array Buffer
		VAO();

		//! Deleted the Vertex Array Buffer
		~VAO();

		//! Binds the Vertex Array Buffer
		void Bind();

		//! Unbinds the Vertex Array Buffer
		void Unbind();

		//! Enables a Vertex Array Attribute and pushes the Layout
		void PushVertexAttrib(const VAOLayout& vaoLayout);

		//! Disables the Vertex Array Attribute with the given Index
		void PopVertexAttrib(GLint index);

		//! Returns the Buffer ID
		inline GLuint GetBufferID() const { return m_BufferID; }

		//! Returns the Size of the given Type in Bytes
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
		GLuint m_BufferID;

	};
}