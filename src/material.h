#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

struct material {
        const struct spectrum fdr; // diffuse reflection curve
};

extern struct material material_gold;

#endif
