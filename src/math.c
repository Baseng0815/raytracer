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

void fvec3_normalize(struct fvec3 *vec)
{
        double len_squared = fvec3_len_squared(vec);
        double inverse_len = 1 / sqrt(len_squared);
        vec->x *= inverse_len;
        vec->y *= inverse_len;
        vec->z *= inverse_len;
}

void fvec3_print(const struct fvec3 *vec)
{
        printf("[%f %f %f]\n", vec->x, vec->y, vec->z);
}
