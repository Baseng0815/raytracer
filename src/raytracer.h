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

void raytracer_render(const struct scene*, int iw, int ih, int sw, int sh);

#endif
