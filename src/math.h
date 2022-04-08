#ifndef MATH_H
#define MATH_H

#include <stdbool.h>

#define PI 3.14159265359
#define PI_INVERSE 0.31830988618
#define E 0.00001

struct fvec3 {
        double x;
        double y;
        double z;
};

struct fmat3 {
        double v[3][3];
};

extern struct fvec3 fvec3_left;
extern struct fvec3 fvec3_right;
extern struct fvec3 fvec3_up;
extern struct fvec3 fvec3_down;
extern struct fvec3 fvec3_front;
extern struct fvec3 fvec3_back;

double fmax(double, double);
double interpolate_array(const double*, double);

double fvec3_len_squared(const struct fvec3*);
double fvec3_dot(const struct fvec3*, const struct fvec3*);
bool fvec3_is_null(const struct fvec3*);
void fvec3_add(struct fvec3*, const struct fvec3*, const struct fvec3*);
void fvec3_sub(struct fvec3*, const struct fvec3*, const struct fvec3*);
void fvec3_mult(struct fvec3*, const struct fvec3*, double);
void fvec3_cross(struct fvec3*, const struct fvec3*, const struct fvec3*);
void fvec3_negate(struct fvec3*, const struct fvec3*);
void fvec3_normalize(struct fvec3*, const struct fvec3*);
void fvec3_print(const struct fvec3*);

void fmat3_mult(struct fmat3*, const struct fmat3*, const struct fmat3*);
void fmat3_vecmult(struct fvec3*, const struct fmat3*, const struct fvec3*);

#endif
