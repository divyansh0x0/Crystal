#pragma once
#include "crystal/layout/Size.h"
namespace crystal::graphics{

    class ApiContextManager{

    public:
        virtual ~ApiContextManager() = default;
        virtual void switchContextToCurrentThread() = 0;
        /**
         * Must always be called after switchContextToCurrentThread otherwise no other thread will be able to call switchContextToCurrentThread
         */
        virtual void detachContextFromCurrentThread() = 0;
        virtual void swapBuffers() = 0;
        virtual const crystal::layout::Size&  getFrameBufferSize() = 0;
        
    };
}