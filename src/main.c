#include <stdio.h>

#include "ray.h"
#include "geometry.h"
#include "raytracer.h"

#include "image.h"

int main(int argc, char *argv[])
{

        /* struct sphere spheres[1]; */
        /* spheres[0].equator = fvec3_right; */
        /* spheres[0].pole = fvec3_up; */
        /* printf("%lu\n", sizeof(spheres)); */

        /* raytracer_render(NULL, 100, 100, 200, 200); */

        struct image_pixel pixels[256 * 256];
        for (size_t i = 0; i < 256 * 256; i++) {
                pixels[i].r = i / 256;
                pixels[i].g = 0;
                pixels[i].b = (255 - i / 256);
        }

        image_save("image.bmp", pixels, 256, 256, BMP);

        return 0;
}
