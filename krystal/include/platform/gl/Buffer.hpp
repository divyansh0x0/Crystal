#pragma once

#include "krystal/graphics/Buffer.hpp"
#include <glad/glad.h>
namespace platform::gl
{
    class VertexBuffer final : public ktl::graphics::VertexBuffer
    {
        private:
             GLuint m_ID = 0;
        public:
            VertexBuffer() = delete;
            explicit VertexBuffer(const GLfloat vertices[], size_t array_length);

            void bind() override;
            void unbind() override;
            ~VertexBuffer() override;
    };

    class IndexBuffer final : public ktl::graphics::IndexBuffer
    {

        private:
            GLuint m_ID = 0;
        public:
            IndexBuffer() = delete;
            explicit IndexBuffer(const GLuint indices[], size_t array_length);

            void bind() override;
            void unbind() override;
            ~IndexBuffer() override;
    };
} // namespace platform::gl