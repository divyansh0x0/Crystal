//
// Created by Anon on 7/28/2025.
//

#include "platform/gl/Buffer.hpp"

#include <glad/glad.h>

#include "krystal/core/Logger.hpp"

#include "platform/gl/Helper.hpp"

namespace platform::gl
{
    /* ****************************************************************************************************************/
    /* ********************************************* VERTEX BUFFER  ***************************************************/
    /* ****************************************************************************************************************/
    VertexBuffer::VertexBuffer(const GLfloat vertices[], const size_t array_length)
    {
        // Generate a buffer to store vertices
        GL_CALL(glGenBuffers(1, &m_ID));
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
        // Copy vertex data to buffer, the original data is not needed anymore
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, array_length * sizeof(GLuint), vertices, GL_STATIC_DRAW));
    }

    void VertexBuffer::bind()
    {
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
    }

    void VertexBuffer::unbind()
    {
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    VertexBuffer::~VertexBuffer()
    {
        logger::Info(std::to_string(m_ID) + " Destroyed");
        if (m_ID == 0) return;
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GL_CALL(glDeleteBuffers(1, &m_ID));
    }

    /* ****************************************************************************************************************/
    /* ********************************************* INDEX BUFFER  ***************************************************/
    /* ****************************************************************************************************************/

    IndexBuffer::IndexBuffer(const GLuint indices[], const size_t array_length)
    {
        // Generate a buffer to store vertices
        GL_CALL(glGenBuffers(1, &m_ID));
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
        // Copy vertex data to buffer, the original data is not needed anymore
        GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, array_length * sizeof(GLfloat), indices, GL_STATIC_DRAW));
    }

    void IndexBuffer::bind()
    {
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
    }

    void IndexBuffer::unbind()
    {
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    IndexBuffer::~IndexBuffer()
    {
        if (m_ID == 0) return;

        logger::Info(std::to_string(m_ID) + " Destroyed");
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GL_CALL(glDeleteBuffers(1, &m_ID));
    };

} // namespace platform::gl