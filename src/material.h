#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

struct material {
        const struct spectrum *fdr; // diffuse reflection curve
        const struct spectrum *fsr[10]; // specular reflection curve (10deg steps)
};

extern struct material mat_1;
extern struct material mat_white;

// get the specular reflection curve at a certain wavelength and angle ([0;pi/2])
double material_get_fsr(const struct material*, double, double);

#endif
