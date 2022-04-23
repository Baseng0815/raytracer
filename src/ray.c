#include "ray.h"

#include "geometry.h"

#include <math.h>
#include <stdio.h>

void ray_get_point(struct fvec3 *out, const struct ray *ray, double t)
{
        struct fvec3 intersect_dir;
        fvec3_mult(&intersect_dir, &ray->direction, t);
        fvec3_add(out, &ray->origin, &intersect_dir);
}

bool ray_intersect_with_sphere(struct intersect *intersect,
                               const struct ray *ray,
                               const struct sphere *sphere)
{
        /* precomputed constants */
        double sr2 = sphere->radius * sphere->radius;

        /* 1. find distance squared between ray origin and center */
        struct fvec3 oc;
        fvec3_sub(&oc, &sphere->origin, &ray->origin);
        double l2oc = fvec3_len_squared(&oc);
        bool in_sphere = l2oc < sr2;

        /* 2. calculate ray distance which is closest to center */
        double tca = fvec3_dot(&oc, &ray->direction);

        /* 3. test if ray is outside and points away from sphere */
        if (!in_sphere && tca < 0.0) {
                return false;
        }

        /* 4. find square of half-chord intersection distance */
        double t2hc = sr2 - l2oc + tca * tca;

        /* 5. test if square is negative */
        if (!in_sphere && t2hc < 0.0) {
                return false;
        }

        /* 6. calculate intersection distance */
        double t;
        if (in_sphere) {
                t = tca + sqrt(t2hc);
        } else {
                t = tca - sqrt(t2hc);
        }

        /* 7. find intersection point */
        ray_get_point(&intersect->point, ray, t);
        intersect->distance = t;

        /* 8. find intersection normal */
        double sri = 1.0 / sphere->radius;
        intersect->normal.x = (intersect->point.x - sphere->origin.x) * sri;
        intersect->normal.y = (intersect->point.y - sphere->origin.y) * sri;
        intersect->normal.z = (intersect->point.z - sphere->origin.z) * sri;

        /* now use spherical inverse mapping to find texture coordinates */
        struct fvec3 tmp;
        fvec3_negate(&tmp, &intersect->normal);
        double phi = fvec3_dot(&tmp, &sphere->pole);
        intersect->v = phi * PI_INVERSE;
        intersect->u = acos(fvec3_dot(&sphere->equator, &intersect->normal)
                            / sin(phi)) * 0.5 * PI_INVERSE;
        fvec3_cross(&tmp, &sphere->pole, &sphere->equator);
        /* invert u if necessary */
        if (fvec3_dot(&tmp, &intersect->normal) >= 0.0) {
                intersect->u = 1.0 - intersect->u;
        }

        return true;
}

bool ray_intersect_with_plane(struct intersect *intersect,
                              const struct ray *ray,
                              const struct plane *plane)
{
        /* 1. calculate d and compare it to zero (using epsilon) */
        double vd = fvec3_dot(&plane->normal, &ray->direction);
        if (vd < E) {
                return false;
        }

        /* 2. calculate v0 and t and compare t to zero */
        double v0 = -(fvec3_dot(&plane->normal, &ray->origin) + plane->d);
        double t = v0 / vd;
        if (t <= 0) {
                return false;
        }

        /* 3. compute intersection point */
        ray_get_point(&intersect->point, ray, t);
        intersect->distance = t;

        /* 4. compare v0 to zero and reverse normal */
        if (vd >= 0.0) {
                fvec3_negate(&intersect->normal, &plane->normal);
        } else {
                intersect->normal = plane->normal;
        }

        return true;
}

void ray_reflect(struct ray *out,
                 const struct ray *ray,
                 const struct intersect *intersect)
{
        out->origin = intersect->point;
        fvec3_mult(&out->direction,
                   &intersect->normal,
                   2.0 * fvec3_dot(&intersect->normal, &ray->direction));
        fvec3_sub(&out->direction,
                  &ray->direction, &out->direction);
}

void ray_refract(struct ray *out,
                 const struct ray *ray,
                 const struct intersect *intersect,
                 double nit)
{
        out->origin = intersect->point;
        /* nit = st/si = n1/2 */
        double ci = fvec3_dot(&ray->direction, &intersect->normal);
        double si = sin(acos(ci));

        fvec3_mult(&out->direction, &ray->direction, nit);
        struct fvec3 tmp;
        fvec3_mult(&tmp, &intersect->normal, nit*ci - sqrt(1.0-nit*nit*si*si));
        fvec3_add(&out->direction, &out->direction, &tmp);
}
