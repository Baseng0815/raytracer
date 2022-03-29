#include <stdio.h>

#include "ray.h"
#include "geometry.h"
#include "raytracer.h"

#include "image.h"

#include "color.h"

int main(int argc, char *argv[])
{
        struct fvec3 xyz;
        spectrum_to_xyz(&xyz, &d65);
        printf("%f %f %f\n", xyz.x, xyz.y, xyz.z);

        struct fvec3 rgb;
        fmat3_vecmult(&rgb, &xyztorgb, &xyz);
        printf("%f %f %f\n", rgb.x, rgb.y, rgb.z);

        return 0;
        struct fmat3 m = {
                {
                        {1.0, 2.0, 3.0},
                        {4.0, 5.0, 6.0},
                        {7.0, 8.0, 9.0}
                }
        };

        struct fmat3 out;
        fmat3_mult(&out, &m, &m);
        for (size_t row = 0; row < 3; row++) {
                printf("%f %f %f\n", out.v[row][0], out.v[row][1], out.v[row][2]);
        }

        struct fvec3 v = {
                .x = 1.0,
                .y = 1.0,
                .z = 1.0
        };

        struct fvec3 f;
        fmat3_vecmult(&f, &out, &v);
        printf("%f %f %f\n", f.x, f.y, f.z);

        return 0;
        struct sphere spheres[1];
        spheres[0].equator = fvec3_right;
        spheres[0].pole = fvec3_up;
        spheres[0].origin.x = 0.0;
        spheres[0].origin.y = 0.0;
        spheres[0].origin.z = 5.0;
        spheres[0].radius = 2.0;

        struct scene scene = {
                .spheres = spheres,
                .sphere_count = 1,
                .sw = 2.0,
                .sh = 2.0
        };

        spectrum_set_intensity(&scene.background, 700.0, 0.4);
        spectrum_set_intensity(&scene.background, 700.0, 0.6);
        spectrum_set_intensity(&scene.background, 700.0, 0.2);
        printf("%f\n", spectrum_integrate(&d65));

        raytracer_render(&scene, 1024, 1024);

        return 0;
}
