#pragma once
#include "krystal/graphics/Renderer.hpp"

#include "Buffer.hpp"
#include "Shader.hpp"

namespace platform::gl
{

    class Renderer : public ktl::graphics::Renderer
    {
        public:
            explicit Renderer(ktl::WindowContext* window_context)
                : ktl::graphics::Renderer(window_context) {

                  };
            void init() override;
            void destroy() override;
            void render() override;
            ~Renderer() override;

        private:
            bool                     m_initialized_flag = false;
            bool                     m_destroyed_flag   = false;
            ktl::Owned<Shader>       m_shader;
            ktl::Owned<IndexBuffer>  m_index_buffer;
            ktl::Owned<VertexBuffer> m_vertex_buffer;
    };
} // namespace platform::gl