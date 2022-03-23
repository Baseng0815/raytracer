#include <stdio.h>

#include "ray.h"
#include "geometry.h"
#include "raytracer.h"

int main(int argc, char *argv[])
{

        struct sphere spheres[1];
        spheres[0].equator = fvec3_right;
        spheres[0].pole = fvec3_up;
        spheres[0].origin = 

        raytracer_render(NULL, 100, 100, 200, 200);

        return 0;
}
