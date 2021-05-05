#pragma once

struct Color
{
    uint8_t color[4];
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
        color[3] = a;
    }
    Color(uint8_t r, uint8_t g, uint8_t b) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
        color[3] = 255;
    }
};