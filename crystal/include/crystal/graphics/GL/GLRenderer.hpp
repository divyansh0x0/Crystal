#include "crystal/graphics/Renderer.hpp"

namespace crystal::graphics
{

    class GLRenderer : public Renderer
    {
        public:
            GLRenderer () {};
            void init () override;
            void destroy () override;
            void render () override;
            ~GLRenderer ();

        private:
            bool m_initialized_flag = false;
            bool m_destroyed_flag   = false;
    };
} // namespace crystal::graphics