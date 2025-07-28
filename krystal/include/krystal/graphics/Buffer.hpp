#pragma once
#include <cinttypes>

namespace ktl::graphics
{
    class VertexBuffer
    {
        public:
            virtual void bind()     = 0;
            virtual void unbind()   = 0;
            virtual ~VertexBuffer() = default;
    };

    class IndexBuffer
    {
        public:
            virtual void bind()    = 0;
            virtual void unbind()  = 0;
            virtual ~IndexBuffer() = default;
    };
} // namespace ktl::graphics