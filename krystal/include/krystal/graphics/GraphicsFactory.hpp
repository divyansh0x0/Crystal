#pragma once
#include "Buffer.hpp"
#include "platform/gl/Shader.hpp"

namespace ktl::graphics
{
    enum class API;

    class GraphicsFactory
    {
        public:
            explicit GraphicsFactory(const API graphics_api) : m_graphics_api(graphics_api) {};
            VertexBuffer* CreateVertexBuffer(const float vertices[], size_t size) const;
            IndexBuffer*  CreateIndexBuffer(const uint32_t indices[], size_t size) const;
            Shader* CreateShader(const char* vertex_shader_code, const char* fragment_shader_code) const;

        private:
            API m_graphics_api;
    };
}; // namespace ktl::graphics
