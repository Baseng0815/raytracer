#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

// standard RGBA format
struct image_pixel {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
};

enum image_type {
        BMP
};

void image_save(const char *file,
                const struct image_pixel *pixels,
                int width, int height,
                enum image_type format);

#endif
