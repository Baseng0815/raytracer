#ifndef MATH_H
#define MATH_H

#define PI 3.14159265359
#define PI_INVERSE 0.31830988618

struct fvec3 {
        double x;
        double y;
        double z;
};

double fvec3_len_squared(const struct fvec3 *vec);
double fvec3_dot(const struct fvec3 *vec1, const struct fvec3 *vec2);
void fvec3_normalize(struct fvec3 *vec);
void fvec3_print(const struct fvec3 *vec);

#endif
