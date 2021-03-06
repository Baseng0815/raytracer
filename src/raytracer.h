#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <stddef.h>

#include "math.h"
#include "color.h"

struct light {
        struct fvec3 position;
        const struct spectrum *spectrum;
};

struct scene {
        const struct sphere *spheres;
        const struct plane *planes;
        const struct light *lights;

        const struct spectrum *background;

        size_t sphere_count;
        size_t plane_count;
        size_t light_count;

        double sw;
        double sh;
};

void raytracer_build_tables(void);
void raytracer_render(const struct scene*, int iw, int ih);

#endif
