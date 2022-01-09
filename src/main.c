#include <stdio.h>

#include "ray.h"

int main(int argc, char *argv[])
{
        struct ray ray = {
                .origin = {
                        .x = 1.0,
                        .y = -2.0,
                        .z = -1
                },
                .direction = {
                        .x = 1.0,
                        .y = 2.0,
                        .z = 4.0
                }
        };

        ray.direction = fvec3_normalize(&ray.direction);
        struct sphere sphere = {
                .origin = {
                        .x = 3.0,
                        .y = 0.0,
                        .z = 5.0
                },
                .radius = 3.0
        };

        struct intersection intersect;
        if (ray_intersect_with_sphere(&ray, &sphere, &intersect)) {
                fvec3_print(&intersect.point);
                fvec3_print(&intersect.normal);
        }

        return 0;
}
