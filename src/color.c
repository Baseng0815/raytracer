#include "color.h"

#include "math.h"

#include <stddef.h>
#include <stdio.h>
#include <math.h>

struct spectrum d65 = {
        .values = {
                0.8275, 0.9149, 0.9343, 0.8668, 1.0486,
                1.1701, 1.1781, 1.1486, 1.1592, 1.0881,
                1.0935, 1.0780, 1.0479, 1.0769, 1.0441,
                1.0405, 1.0000, 0.9633, 0.9579, 0.8869,
                0.9001, 0.8960, 0.8770, 0.8329, 0.8370,
                0.8003, 0.8021, 0.8228, 0.7828, 0.6972,
                0.7161, 0.7435, 0.6160, 0.6989, 0.7509,
                0.6359, 0.4642, 0.6681, 0.6338, 0.6430
        }
};

struct spectrum x31 = {};
struct spectrum y31 = {};
struct spectrum z31 = {};

struct spectrum spectrum_reddish = {};
struct spectrum spectrum_greenish = {};
struct spectrum spectrum_blueish = {};
struct spectrum spectrum_dark = {};

static struct fmat3 xyztorgb = {
        .v = {
                { 3.2406255, -1.5372080, -0.4986286 },
                { -0.9689307, 1.8757561, 0.0415175 },
                { 0.0557101, -0.2040211, 1.0569959 }
        }
};

void color_build_tables(void)
{
        for (size_t i = 0; i < SPECTRUM_DATAPOINTS; i++) {
                double wl = 400.0 + (400.0 / SPECTRUM_DATAPOINTS) * i;
                x31.values[i] = 1.065 * exp(-0.5 * pow((wl - 595.8) / 33.33, 2.0))
                        + 0.366 * exp(-0.5 * pow((wl-446.8) / 19.44, 2.0));
                y31.values[i] = 1.014 * exp(-0.5 * pow((log(wl) - log(556.3)) / 0.075, 2.0));
                z31.values[i] = 1.839 * exp(-0.5 * pow((log(wl) - log(449.8)) / 0.051, 2.0));

                spectrum_reddish.values[i] = exp(-pow(wl - 650.0, 2.0) / 1000.0);
                spectrum_greenish.values[i] = exp(-pow(wl - 500.0, 2.0) / 1000.0);
                spectrum_blueish.values[i] = exp(-pow(wl - 450, 2.0) / 1000.0);
                spectrum_dark.values[i] = 0.1;
        }
}

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
        return interpolate_array(spectrum->values, d);
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

double spectrum_integrate(const struct spectrum *s)
{
        double sum = 0.0;
        double width = 400.0 / SPECTRUM_DATAPOINTS;
        for (size_t i = 0; i < SPECTRUM_DATAPOINTS; i++) {
                sum += s->values[i] * width;
        }

        return sum;
}

void spectrum_to_xyz(struct fvec3 *out, const struct spectrum *s)
{
        struct spectrum mult;
        spectrum_multiply(&mult, &x31, s);
        out->x = spectrum_integrate(&mult);
        spectrum_multiply(&mult, &y31, s);
        out->y = spectrum_integrate(&mult);
        spectrum_multiply(&mult, &z31, s);
        out->z = spectrum_integrate(&mult);

        // fix Y at 1.0 for white point (Y=105.081890 for D65)
        fvec3_mult(out, out, 1.0 / 105.081890);
}

void xyz_to_rgb(struct fvec3 *rgb, const struct fvec3 *xyz)
{
        // linear conversion
        fmat3_vecmult(rgb, &xyztorgb, xyz);

        // apply gamma correction
        rgb->x = rgb->x <= 0.0031308 ? (12.92 * rgb->x)
                : (1.055 * powf(rgb->x, 1/2.4) - 0.055);
        rgb->y = rgb->y <= 0.0031308 ? (12.92 * rgb->y)
                : (1.055 * powf(rgb->y, 1/2.4) - 0.055);
        rgb->z = rgb->z <= 0.0031308 ? (12.92 * rgb->z)
                : (1.055 * powf(rgb->z, 1/2.4) - 0.055);

        // clip to [0.0; 1.0]
        rgb->x = rgb->x < 0.0 ? 0.0 : rgb->x > 1.0 ? 1.0 : rgb->x;
        rgb->y = rgb->y < 0.0 ? 0.0 : rgb->y > 1.0 ? 1.0 : rgb->y;
        rgb->z = rgb->z < 0.0 ? 0.0 : rgb->z > 1.0 ? 1.0 : rgb->z;
}
