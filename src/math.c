#include "math.h"

#include <math.h>
#include <stdio.h>

struct fvec3 fvec3_left     = { .x = -1.0 };
struct fvec3 fvec3_right    = { .x = 1.0 };
struct fvec3 fvec3_up       = { .y = 1.0 };
struct fvec3 fvec3_down     = { .y = -1.0 };
struct fvec3 fvec3_front    = { .z = 1.0 };
struct fvec3 fvec3_back     = { .z = -1.0 };

double fvec3_len_squared(const struct fvec3 *vec)
{
        return vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
}

double fvec3_dot(const struct fvec3 *vec1, const struct fvec3 *vec2)
{
        return vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
}

bool fvec3_is_null(const struct fvec3 *vec)
{
        return vec->x == 0.0 && vec->y == 0.0 && vec->z == 0.0;
}

void fvec3_add(struct fvec3 *out,
               const struct fvec3 *vec1,
               const struct fvec3 *vec2)
{
        out->x = vec1->x + vec2->x;
        out->y = vec1->y + vec2->y;
        out->z = vec1->z + vec2->z;
}

void fvec3_sub(struct fvec3 *out,
               const struct fvec3 *vec1,
               const struct fvec3 *vec2)
{
        out->x = vec1->x - vec2->x;
        out->y = vec1->y - vec2->y;
        out->z = vec1->z - vec2->z;
}
void fvec3_mult(struct fvec3 *out,
                const struct fvec3 *vec,
                double scalar)
{
        out->x = vec->x * scalar;
        out->y = vec->y * scalar;
        out->z = vec->z * scalar;
}

void fvec3_cross(struct fvec3 *out,
                 const struct fvec3 *vec1,
                 const struct fvec3 *vec2)
{
        out->x = vec1->y * vec2->z - vec1->x * vec2->y;
        out->y = vec1->z * vec2->x - vec1->x * vec2->z;
        out->y = vec1->x * vec2->y - vec1->y * vec2->x;
}

void fvec3_negate(struct fvec3 *out,
                  const struct fvec3 *vec)
{
        out->x = -vec->x;
        out->y = -vec->y;
        out->z = -vec->z;
}

void fvec3_normalize(struct fvec3 *out,
                     const struct fvec3 *vec)
{
        double len_squared = fvec3_len_squared(vec);
        double inverse_len = 1.0 / sqrt(len_squared);
        out->x = vec->x * inverse_len;
        out->y = vec->y * inverse_len;
        out->z = vec->z * inverse_len;
}

void fvec3_print(const struct fvec3 *vec)
{
        printf("[%f %f %f]\n", vec->x, vec->y, vec->z);
}
