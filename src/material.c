#include "material.h"

#include "math.h"
#include <math.h>
#include <stddef.h>

struct material mat_1 = {
        .fdr = &spectrum_greenish
};

struct material mat_white = {
        .fdr = &d65
};

double material_get_fsr(const struct material *mat, double wl, double t)
{
        double degrees = t * 180.0 / M_PI;
        if (degrees < 0 || degrees > 90) {
                return 0.0;
        }
        return 0.0;

        /* double d = degrees / 10.0; */
        /* if (d - (size_t)d < 0.00001) { */
        /*         // no interpolation necessary */
        /*         return spectrum_get_intensity(mat->fsr[(size_t)d], wl); */
        /* } */

        /* double lower = *mat->fsr[(size_t)(d + 0.0)]; */
        /* double upper = *mat->fsr[(size_t)(d + 1.0)]; */

        /* double blend = d - (int)d; */
        /* return upper * blend + lower * (1.0 - blend); */
}
