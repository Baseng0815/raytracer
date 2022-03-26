#include <stdio.h>

#include "ray.h"
#include "geometry.h"
#include "raytracer.h"

#include "image.h"

int main(int argc, char *argv[])
{

        struct sphere spheres[1];
        spheres[0].equator = fvec3_right;
        spheres[0].pole = fvec3_up;
        spheres[0].origin.x = 0.0;
        spheres[0].origin.y = 0.0;
        spheres[0].origin.z = 5.0;
        spheres[0].radius = 2.0;

        struct scene scene = {
                .spheres = spheres,
                .sphere_count = 1
        };

        raytracer_render(&scene, 100, 100, 2, 2);

        return 0;
}
