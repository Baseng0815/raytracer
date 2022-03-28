#include "color.h"

#include <stddef.h>
#include <stdio.h>

struct spectrum d65_standard_illuminant = {
        .values = { 82.75, 91.49, 93.43, 86.68, 104.86,
                117.01, 117.81, 114.86, 115.92, 108.81,
                109.35, 107.80, 104.79, 107.69, 104.41,
                104.05, 100.0, 96.33, 95.79, 88.69,
                90.01, 89.60, 87.70, 83.29, 83.70,
                80.03, 80.21, 82.28, 78.28, 69.72,
                71.61, 74.35, 61.60, 69.89, 75.09,
                63.59, 46.42, 66.81, 63.38, 64.30 }
};

void spectrum_set_intensity(struct spectrum *s, double w, double intensity)
{
        if (w < 400.0 || w > 790.0) {
                return;
        }

        size_t i = (w - 400.0) / SPECTRUM_DATAPOINTS;
        s->values[i] = intensity;
}

double spectrum_get_intensity(const struct spectrum *spectrum, double w)
{
        if (w < 400.0 || w > 790.0) {
                return 0;
        }

        double d = (w - 400.0) / SPECTRUM_DATAPOINTS;
        double lower = spectrum->values[(size_t)(d + 0)];
        double upper = spectrum->values[(size_t)(d + 1)];

        // interpolate
        double blend = d - (int)d;
        return upper * blend + lower * (1.0 - blend);
}

void spectrum_fmultiply(struct spectrum *out, const struct spectrum *s, double f)
{
        for (size_t i = 0; i < SPECTRUM_DATAPOINTS; i++) {
                out->values[i] = s->values[i] * f;
        }
}

void spectrum_multiply(struct spectrum *out,
                       const struct spectrum *s1,
                       const struct spectrum *s2)
{
        for (size_t i = 0; i < SPECTRUM_DATAPOINTS; i++) {
                out->values[i] = s1->values[i] * s2->values[i];
        }
}

void spectrum_add(struct spectrum *out,
                  const struct spectrum *s1,
                  const struct spectrum *s2)
{
        for (size_t i = 0; i < SPECTRUM_DATAPOINTS; i++) {
                out->values[i] = s1->values[i] + s2->values[i];
        }
}
