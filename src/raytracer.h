#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <stddef.h>

#include "math.h"

struct sphere;
struct plane;

struct scene {
        struct sphere *spheres;
        struct plane *planes;

        size_t sphere_count;
        size_t plane_count;
};

/* sw/sh = screen width/height (final image resolution)
 * ww/wh = world width/height (image plane world size) */
void raytracer_render(const struct scene*, int sw, int sh, int ww, int wh);

#endif
