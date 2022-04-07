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
        xyz_to_rgb(&rgb, &xyz);
        printf("%f %f %f\n", rgb.x, rgb.y, rgb.z);
        printf("%f %f %f\n", rgb.x * 255, rgb.y * 255, rgb.z * 255);

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
