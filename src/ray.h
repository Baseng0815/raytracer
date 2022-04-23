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
        double distance;
        double u;
        double v;
};

void ray_get_point(struct fvec3*, const struct ray*, double);

bool ray_intersect_with_sphere(struct intersect*,
                               const struct ray*,
                               const struct sphere*);

bool ray_intersect_with_plane(struct intersect*,
                              const struct ray*,
                              const struct plane*);

/* perfect specular reflection */
void ray_reflect(struct ray*, const struct ray*, const struct intersect*);

/* perfect specular transmission */
void ray_refract(struct ray*,
                 const struct ray*,
                 const struct intersect*,
                 double);

#endif
