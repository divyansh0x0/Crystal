#include<core/Color.h>

quartz::Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
    rgba.r = r;
    rgba.g = g;
    rgba.b = b;
    rgba.a = a;
}
const quartz::RGBA& quartz::Color::getRGBA(){
    return rgba;
}