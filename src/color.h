#ifndef COLOR_H
#define COLOR_H

#define SPECTRUM_DATAPOINTS 40

struct fvec3;

struct spectrum {
        double values[SPECTRUM_DATAPOINTS]; // [400nm; 800nm)
};

extern struct spectrum d65; // standard illuminant 65 (natural daylight)

// CIE XYZ color matching approximation
extern struct spectrum x31;
extern struct spectrum y31;
extern struct spectrum z31;

void spectrum_set_intensity(struct spectrum*, double, double);
double spectrum_get_intensity(const struct spectrum*, double);
void spectrum_fmultiply(struct spectrum*, const struct spectrum*, double);
void spectrum_multiply(struct spectrum*,
                       const struct spectrum*,
                       const struct spectrum*);
void spectrum_add(struct spectrum*,
                  const struct spectrum*,
                  const struct spectrum*);

double spectrum_integrate(const struct spectrum*);
void spectrum_to_xyz(struct fvec3*, const struct spectrum*);

void xyz_to_rgb(struct fvec3*, const struct fvec3*);

#endif
