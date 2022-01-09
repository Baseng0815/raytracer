#include "math.h"

#include <math.h>
#include <stdio.h>

double fvec3_len_squared(const struct fvec3 *vec)
{
        return vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
}

double fvec3_dot(const struct fvec3 *vec1, const struct fvec3 *vec2)
{
        return vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
}

struct fvec3 fvec3_add(const struct fvec3 *vec1, const struct fvec3 *vec2)
{
        struct fvec3 new_vec = {
                .x = vec1->x + vec2->x,
                .y = vec1->y + vec2->y,
                .z = vec1->z + vec2->z
        };

        return new_vec;
}

struct fvec3 fvec3_sub(const struct fvec3 *vec1, const struct fvec3 *vec2)
{
        struct fvec3 new_vec = {
                .x = vec1->x - vec2->x,
                .y = vec1->y - vec2->y,
                .z = vec1->z - vec2->z
        };

        return new_vec;
}
struct fvec3 fvec3_mult(const struct fvec3 *vec, double scalar)
{
        struct fvec3 new_vec = {
                .x = vec->x * scalar,
                .y = vec->y * scalar,
                .z = vec->z * scalar
        };

        return new_vec;
}

struct fvec3 fvec3_negate(const struct fvec3 *vec1)
{
        struct fvec3 new_vec = {
                .x = -vec1->x,
                .y = -vec1->y,
                .z = -vec1->z
        };

        return new_vec;
}

struct fvec3 fvec3_normalize(const struct fvec3 *vec)
{
        double len_squared = fvec3_len_squared(vec);
        double inverse_len = 1.0 / sqrt(len_squared);
        struct fvec3 new_vec = {
                .x = vec->x * inverse_len,
                .y = vec->y * inverse_len,
                .z = vec->z * inverse_len
        };

        return new_vec;
}

void fvec3_print(const struct fvec3 *vec)
{
        printf("[%f %f %f]\n", vec->x, vec->y, vec->z);
}
