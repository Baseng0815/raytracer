#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <stddef.h>

#include "math.h"
#include "color.h"

struct sphere;
struct plane;

struct light {
        struct fvec3 position;
        struct spectrum spectrum;
};

struct scene {
        struct sphere *spheres;
        struct plane *planes;
        struct light *lights;

        struct spectrum background;

        size_t sphere_count;
        size_t plane_count;
        size_t light_count;

        double sw;
        double sh;
};

void raytracer_render(const struct scene*, int iw, int ih);

#endif
