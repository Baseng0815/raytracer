#ifndef RAY_H
#define RAY_H

#include <stdbool.h>

#include "math.h"

struct sphere;
struct plane;

struct ray {
        struct fvec3 origin;
        struct fvec3 direction;
};

struct intersect {
        struct fvec3 point;
        struct fvec3 normal;
        double u;
        double v;
};

void ray_get_point(struct fvec3*, const struct ray*, double);

bool ray_intersect_with_sphere(struct intersect *intersect,
                               const struct ray *ray,
                               const struct sphere *sphere);

bool ray_intersect_with_plane(struct intersect *intersect,
                              const struct ray *ray,
                              const struct plane *sphere);

#endif
