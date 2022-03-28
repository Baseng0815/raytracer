#ifndef COLOR_H
#define COLOR_H

#define SPECTRUM_DATAPOINTS 40

struct spectrum {
        double values[SPECTRUM_DATAPOINTS]; // [400nm; 800nm)
};

extern struct spectrum d65_standard_illuminant; // natural daylight

void spectrum_set_intensity(struct spectrum*, double, double);
double spectrum_get_intensity(const struct spectrum*, double);
void spectrum_fmultiply(struct spectrum*, const struct spectrum*, double);
void spectrum_multiply(struct spectrum*,
                       const struct spectrum*,
                       const struct spectrum*);
void spectrum_add(struct spectrum*,
                  const struct spectrum*,
                  const struct spectrum*);

#endif
