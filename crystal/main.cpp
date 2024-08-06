#include <core/logger.h>
#include <ui/window.h>
quartz::Size window_size = quartz::Size(800, 600);

int main() {
    quartz::Window window = quartz::Window("Crystal", window_size, quartz::Color(255, 255, 255, 255));
    window.loop();
    return 0;
}
