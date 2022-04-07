#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "math.h"
#include "material.h"

struct sphere {
        const struct material *material;

        struct fvec3 origin;
        double radius;
        /* texture mapping
         * pole:        v=1
         * -pole:       v=0
         * equator:     u=0
         * -equator:    u=1 */
        struct fvec3 pole;
        struct fvec3 equator;
};

struct plane {
        struct fvec3 normal;
        double d;
};

#endif
