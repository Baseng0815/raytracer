#include <stdio.h>

#include "ray.h"
#include "geometry.h"
#include "raytracer.h"

#include "image.h"

#include "color.h"

int main(int argc, char *argv[])
{
        /* struct sphere spheres[1]; */
        /* spheres[0].equator = fvec3_right; */
        /* spheres[0].pole = fvec3_up; */
        /* spheres[0].origin.x = 0.0; */
        /* spheres[0].origin.y = 0.0; */
        /* spheres[0].origin.z = 5.0; */
        /* spheres[0].radius = 2.0; */

        /* struct scene scene = { */
        /*         .spheres = spheres, */
        /*         .sphere_count = 1, */
        /*         .background = d65, */
        /*         .sw = 2.0, */
        /*         .sh = 2.0 */
        /* }; */

        raytracer_build_tables();
        /* raytracer_render(&scene, 1024, 1024); */

        struct fvec3 rgb;
        spectrum_to_xyz(&rgb, &spectrum_reddish);
        xyz_to_rgb(&rgb, &rgb);
        printf("%f %f %f\n", rgb.x, rgb.y, rgb.z);

        return 0;
}
