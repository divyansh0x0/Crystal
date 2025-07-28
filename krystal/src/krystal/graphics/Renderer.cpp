#include "krystal/graphics/Renderer.hpp"
#include "krystal/core/Logger.hpp"

static auto getCurrentTime()
{
    return std::chrono::steady_clock::now().time_since_epoch();
}

namespace ktl::graphics
{
    Renderer::Renderer(WindowContext* window_context)
    {
        m_window_context = window_context;
    }

    void Renderer::start()
    {
        m_running = true;
        m_window_context->detachContextFromCurrentThread();
        m_rendering_thread = std::make_unique<std::thread>(&Renderer::loop, this);
    }

    void Renderer::loop()
    {
        m_window_context->switchContextToCurrentThread();
        this->init();

        using namespace std::chrono_literals;

        auto frame_start_time = getCurrentTime();
        auto accumulated_time = 0ns;

        const auto frame_time = std::chrono::nanoseconds(1000 * 1000 * 1000 / m_max_fps);
        while (m_running)
        {

            const auto frame_end_time = getCurrentTime();
            const auto dt             = frame_end_time - frame_start_time;

            if (dt < frame_time)
            {
                std::this_thread::yield();
                continue;
            }


            this->render();
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
        this->destroy();
        m_window_context->detachContextFromCurrentThread();
    }

    void Renderer::stop()
    {
        logger::Info("Stopping Render loop");
        if (!m_running) return;

        m_running = false;
        if (m_rendering_thread.get() && m_rendering_thread->joinable())
        {
            m_rendering_thread->join();
            m_rendering_thread.reset();
            logger::Success("Renderer", "Render thread stopped");
        }
    }

    Renderer::~Renderer()
    {
        stop();
        m_window_context = nullptr;
    }

} // namespace ktl::graphics