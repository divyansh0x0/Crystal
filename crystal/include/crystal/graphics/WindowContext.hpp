#pragma once
#include "crystal/graphics/Color.hpp"
#include "../geometry/Size.hpp"

namespace crystal
{
    using GLLoadProc = void* (*) (const char* name);

    class WindowContext
    {

        public:
            virtual ~WindowContext()                                             = default;
            [[nodiscard]] virtual const geometry::Size& getFrameBufferSize() const = 0;
            [[nodiscard]] virtual const Color&        getFrameBufferBg() const   = 0;

            virtual void switchContextToCurrentThread() const = 0;

            /**
             * Must always be called after switchContextToCurrentThread otherwise no
             * other thread will be able to call switchContextToCurrentThread
             */
            [[nodiscard]] virtual GLLoadProc getGLLoadProc() const = 0;

            virtual void detachContextFromCurrentThread() const = 0;
            virtual void swapBuffers() const                    = 0;
    };
} // namespace crystal