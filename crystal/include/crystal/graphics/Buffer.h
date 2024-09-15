#pragma once
#include <inttypes.h>
namespace crystal
{
class VertexBuffer
{
    public:
        virtual ~VertexBuffer() = default;
        virtual void bind()     = 0;
        virtual void unbind()   = 0;
        static VertexBuffer *Create(float *vertices, size_t size);
};
class IndexBuffer
{
    public:
        virtual ~IndexBuffer() = default;
        static VertexBuffer *Create(float *vertices, size_t size);
};
} // namespace crystal