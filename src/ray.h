#ifndef RAY_H
#define RAY_H

#include "sphere.h"

#include <stdbool.h>

struct ray {
        struct fvec3 origin;
        struct fvec3 direction;
};

struct intersection {
        struct fvec3 point;
        struct fvec3 normal;
};

bool ray_intersect_with_sphere(const struct ray *ray,
                               const struct sphere *sphere,
                               struct intersection *intersection);

#endif
