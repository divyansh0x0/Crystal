#pragma once
#include "crystal/graphics/Color.hpp"
#include "crystal/layout/Size.hpp"

namespace crystal
{
    typedef void* (*GLLoadProcedure)(const char*);

    class WindowContext
    {

        public:
            virtual ~WindowContext()                                                  = default;
            virtual const crystal::layout::Size& getFrameBufferSize() const           = 0;
            virtual const Color&                 getFrameBufferBg() const                  = 0;

            virtual void                         switchContextToCurrentThread() const = 0;
            /**
             * Must always be called after switchContextToCurrentThread otherwise no
             * other thread will be able to call switchContextToCurrentThread
             */
            virtual void* getGLLoadProc() const                  = 0;
            virtual void  detachContextFromCurrentThread() const = 0;
            virtual void  swapBuffers() const                    = 0;
    };
} // namespace crystal