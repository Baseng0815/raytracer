#include "ray.h"

#include <math.h>
#include <stdio.h>

bool ray_intersect_with_sphere(const struct ray *ray,
                               const struct sphere *sphere,
                               struct intersection *intersection)
{
        /* precomputed constants */
        double sr2 = sphere->radius * sphere->radius;

        /* 1. find distance squared between ray origin and center */
        struct fvec3 oc = fvec3_sub(&sphere->origin, &ray->origin);
        double l2oc = fvec3_len_squared(&oc);
        bool in_sphere = l2oc < sr2;

        /* 2. calculate ray distance which is closest to center */
        double tca = fvec3_dot(&oc, &ray->direction);

        /* 3. test if ray is outside and points away from sphere */
        if (!in_sphere && tca < 0) {
                return false;
        }

        /* 4. find square of half-chord intersection distance */
        double t2hc = sr2 - l2oc + tca * tca;

        /* 5. test if square is negative */
        if (!in_sphere && t2hc < 0) {
                return false;
        }

        /* 6. calculate intersection distance */
        double t;
        if (!in_sphere) {
                t = tca - sqrt(t2hc);
        } else {
                t = tca + sqrt(t2hc);
        }

        /* 7. find intersection point */
        struct fvec3 intersect_dir = fvec3_mult(&ray->direction, t);
        intersection->point = fvec3_add(&ray->origin, &intersect_dir);

        /* 8. find intersection normal */
        double s = 1.0 / sphere->radius;
        intersection->normal.x = (intersection->point.x - sphere->origin.x) * s;
        intersection->normal.y = (intersection->point.y - sphere->origin.y) * s;
        intersection->normal.z = (intersection->point.z - sphere->origin.z) * s;

        return true;
}
