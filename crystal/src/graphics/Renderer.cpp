#include "crystal/graphics/Renderer.hpp"
#include "crystal/core/Logger.hpp"

static auto getCurrentTime()
{
    return std::chrono::steady_clock::now().time_since_epoch();
}

namespace crystal::graphics
{
    void Renderer::start(WindowContext& window_context_ptr)
    {
        m_is_rendering = true;
        window_context_ptr.detachContextFromCurrentThread();
        m_window_context   = &window_context_ptr;
        m_rendering_thread = std::make_unique<std::thread>(&Renderer::loop, this);
    }

    void Renderer::loop()
    {
        m_window_context->switchContextToCurrentThread();
        init();

        using namespace std::chrono_literals;

        auto frame_start_time = getCurrentTime();
        auto accumulated_time = 0ns;

        const auto frame_time = std::chrono::nanoseconds(1000 * 1000 * 1000 / m_max_fps);
        while (m_is_rendering)
        {

            const auto frame_end_time = getCurrentTime();
            const auto dt             = frame_end_time - frame_start_time;

            if (dt < frame_time) continue;


            render();
            m_window_context->swapBuffers();

            frame_start_time = getCurrentTime();

            m_current_fps++;
            accumulated_time += dt;

            if (accumulated_time >= 1s)
            {
                logger::Info("FPS: " + std::to_string(m_current_fps));
                accumulated_time = 0ns;
                m_current_fps    = 0;
            }
        }
    }

    void Renderer::stop()
    {
        logger::Info("Stopping Render loop");
        if (m_is_rendering) m_is_rendering = false;
        if (m_rendering_thread->joinable()) m_rendering_thread->join();

        m_rendering_thread.reset();
    }

    Renderer::~Renderer()
    {
        stop();
        m_window_context = nullptr;
    }

} // namespace crystal::graphics