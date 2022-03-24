#include "image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dib {
        uint32_t size;
        int32_t width;
        int32_t height;
        uint16_t planes;
        uint16_t bits_per_pixel;
        uint32_t compression;
        uint32_t image_size;
        int32_t x_resolution;
        int32_t y_resolution;
        uint32_t num_colors;
        uint32_t important_colors;
};

struct bmp_header {
        uint16_t type;
        uint32_t size;
        uint16_t reserved0;
        uint16_t reserved1;
        uint32_t offset;

        struct dib dib;
} __attribute__((packed));

static void save_bmp(const char *file,
                     const struct image_pixel *pixels,
                     int width, int height);

void image_save(const char *file,
                const struct image_pixel *pixels,
                int width, int height,
                enum image_type format)
{
        switch (format) {
                case BMP:
                        save_bmp(file, pixels, width, height);
                        break;
                default:
                        fprintf(stderr, "file format not recognized");
                        return;
        }
}

void save_bmp(const char *file,
              const struct image_pixel *pixels,
              int width, int height)
{
        if (width & (0x4 - 1)) {
                fprintf(stderr, "width needs to be a multiple of 4");
                return;
        }

        // three channels (24-bit)
        struct bmp_header hdr;
        memset(&hdr, 0, sizeof(struct bmp_header));
        hdr.type = 'B' | ('M' << 8);
        hdr.size = sizeof(struct bmp_header) + 3 * width * height;
        hdr.offset = sizeof(struct bmp_header);
        hdr.dib.size = sizeof(struct dib);
        hdr.dib.width = width;
        hdr.dib.height = height;
        hdr.dib.planes = 1;
        hdr.dib.bits_per_pixel = 24;

        uint8_t *image_data = malloc(3 * width * height);
        for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                        const struct image_pixel *px = &pixels[y * width + x];
                        image_data[(y * width + x) * 3 + 0] = px->b;
                        image_data[(y * width + x) * 3 + 1] = px->g;
                        image_data[(y * width + x) * 3 + 2] = px->r;
                }
        }

        FILE *filp = fopen(file, "w");
        if (!filp) {
                fprintf(stderr, "couldn't open file for saving");
                return;
        }

        fwrite(&hdr, sizeof(hdr), 1, filp);
        fwrite(image_data, 3 * width * height, 1, filp);

        free(image_data);
}
