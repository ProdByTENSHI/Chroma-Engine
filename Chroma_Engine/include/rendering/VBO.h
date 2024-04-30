#pragma once

#include <GL/glew.h>

namespace chroma
{
	//! A Vertex Buffer Object is a Buffer that holds raw Data
	//! This Raw Data gets interpreted by the Shader by passing it's Layout through a VAO
	class VBO
	{
	public:
		//! Generated the Vertex Buffer
		VBO();

		//! Deleted the Vertex Buffer
		~VBO();

		//! Binds the Buffer
		void Bind();

		//! Unbinds the Buffer
		void Unbind();

		//! Binds the Buffer, Sets its Data to \param[in] vertices and Unbinds it after
		void SetBufferData(float vertices[]);

		//! Returns the Buffer ID
		inline GLuint GetBufferID() { return m_BufferID; }

	private:
		GLuint m_BufferID;

	};
}