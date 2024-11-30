#ifndef ASCII_IMPLEMENTATION
#define ASCII_IMPLEMENTATION
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

typedef struct {
    Color c;
} Pixel;

typedef struct {
    size_t w;
    size_t h;
    Pixel *items;
} Screen;

typedef struct {
    size_t x;
    size_t y;
} Vec2;

Screen initScreen(size_t width, size_t height);
void clearBackground(Screen *s, Color color);
void setPixel(Screen *screen, size_t x, size_t y, Color color);
void drawScreen(Screen *screen);
void drawRect(Screen *screen, size_t x, size_t y, size_t w, size_t h, Color color);
void vec2Add(Vec2 vec1, Vec2 vec2); 
void setPixelV(Screen *screen, Vec2 pos, Color color);
void drawRectV(Screen *screen, Vec2 pos, Vec2 size, Color color);

void vec2Add(Vec2 vec1, Vec2 vec2) {
    vec1.x += vec2.x;
    vec1.y += vec2.y;
}

Screen initScreen(size_t width, size_t height) {
    Screen s;
    s.w = width;
    s.h = height;
    s.items = (Pixel *)malloc(sizeof(Pixel) * (s.w * s.h));
    clearBackground(&s, (Color){0,0,0}); 
    return s;
}

void clearBackground(Screen *s, Color color) {
    for (size_t i = 0; i < (s->w * s->h); ++i) {
        s->items[i] = (Pixel){color};
    }
}

void setPixel(Screen *screen, size_t x, size_t y, Color color) {
    screen->items[y * screen->w + x].c = color;
}

void setPixelV(Screen *screen, Vec2 pos, Color color) {
    screen->items[pos.y * screen->w + pos.x].c = color;
}

void drawRect(Screen *screen, size_t x, size_t y, size_t w, size_t h, Color color) {
    for (size_t sy = y; sy < y + h && sy < screen->h; ++sy) {
        for (size_t sx = x; sx < x + w && sx < screen->w; ++sx) {
            setPixelV(screen, (Vec2){sx, sy}, color);
        }
    }
}

void drawRectV(Screen *screen, Vec2 pos, Vec2 size, Color color) {
    for (size_t sy = pos.y; sy < pos.y + size.y && sy < screen->h; ++sy) {
        for (size_t sx = pos.x; sx < pos.x + size.x && sx < screen->w; ++sx) {
            setPixelV(screen, (Vec2){sx, sy}, color);
        }
    }
}

void drawScreen(Screen *screen) {
    printf("\033[H");
    for (size_t y = 0; y < screen->h; ++y) {
        for (size_t x = 0; x < screen->w; ++x) {
            Pixel p = screen->items[y * screen->w + x];
            printf("\033[38;2;%d;%d;%dm█\033[0m", p.c.r, p.c.g, p.c.b);
        }
        printf("\n");
    }
}

void nextFrame(size_t framerate) {
   usleep(1000000/framerate);
   printf("\033[2J\033[H");
}

#endif