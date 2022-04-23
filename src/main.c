#include <stdio.h>

#include "ray.h"
#include "geometry.h"
#include "raytracer.h"

#include "image.h"

#include "color.h"

int main(int argc, char *argv[])
{
        raytracer_build_tables();

        struct sphere spheres[] = {
                (struct sphere) {
                        .equator = fvec3_right,
                        .pole = fvec3_up,
                        .origin = (struct fvec3) {
                                .x = 2.0,
                                .y = 0.0,
                                .z = 5.0
                        },
                        .radius = 2.0,
                        .material = &mat_white
                }
        };

        struct light lights[] = {
                (struct light) {
                        .position = {
                                .x = -1.0,
                                .y = 1.0,
                                .z = 4.0
                        },
                        .spectrum = &spectrum_reddish
                },
                (struct light) {
                        .position = {
                                .x = 0.5,
                                .y = -1.0,
                                .z = 2.0
                        },
                        .spectrum = &spectrum_blueish
                },
                (struct light) {
                        .position = {
                                .x = 1.2,
                                .y = 2.0,
                                .z = 3.0
                        },
                        .spectrum = &spectrum_greenish
                }
        };

        struct scene scene = {
                .spheres = spheres,
                .sphere_count = sizeof(spheres) / sizeof(struct sphere),
                .lights = lights,
                .light_count = sizeof(lights) / sizeof(struct light),
                .background = &spectrum_dark,
                .sw = 2.0,
                .sh = 2.0
        };

        raytracer_render(&scene, 1024, 1024);

        return 0;
}
