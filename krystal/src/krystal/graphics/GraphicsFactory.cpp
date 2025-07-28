//
// Created by Anon on 7/28/2025.
//

#include "krystal/graphics/GraphicsFactory.hpp"

#include "krystal/graphics/Graphics.hpp"

#include "platform/gl/Buffer.hpp"

namespace ktl::graphics
{

    VertexBuffer* GraphicsFactory::CreateVertexBuffer(const float vertices[], const size_t size) const
    {
        switch (m_graphics_api)
        {
            case API::OpenGL:
                return new platform::gl::VertexBuffer(vertices, size);
            default:
                return nullptr;
        }
    }

    IndexBuffer* GraphicsFactory::CreateIndexBuffer(const uint32_t indices[], const size_t size) const
    {
        switch (m_graphics_api)
        {
            case API::OpenGL:
                return new platform::gl::IndexBuffer(indices, size);
            default:
                return nullptr;
        }
    }

    Shader* GraphicsFactory::CreateShader(const char* vertex_shader_code, const char* fragment_shader_code) const
    {
        switch (m_graphics_api)
        {
            case API::OpenGL:
                return new platform::gl::Shader(vertex_shader_code, fragment_shader_code);
            default:
                return nullptr;
        }
    }


} // namespace ktl::graphics