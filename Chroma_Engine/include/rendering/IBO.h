#pragma once

#include <GL/glew.h>

namespace chroma
{
	//! Index Buffer Object
	class IBO
	{
	public:
		//! Generated the Index Buffer and sets the Data
		IBO();

		//! Destroy the Index Buffer
		~IBO();

		//! Binds the IBO
		void Bind();

		//! Unbinds the IBO
		void Unbind();

		//! Binds the Buffer, Sets the Data and Unbinds it
		void SetData(GLint indices[]);

		// Returns the IBO ID
		inline GLuint GetBufferID() const { return m_BufferID; }

	private:
		GLuint m_BufferID;

	};
}