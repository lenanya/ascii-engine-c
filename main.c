#include "ascii.h"

#define WIDTH 100
#define HEIGHT (int)(WIDTH / 2)

int main() {
    Screen s = initScreen(WIDTH, HEIGHT);
    size_t x = 0;
    for (;;) {
        x = (x + 1) % WIDTH;
        clearBackground(&s, (Color){0,0,0});
        drawRectV(&s, (Vec2){x, 10}, (Vec2){10, 5}, (Color){0xff, 0xff, 0xff});
        drawScreen(&s);
        nextFrame(60);
    }
    return 0;
}