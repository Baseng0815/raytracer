#include <stdio.h>

#include "ray.h"
#include "geometry.h"

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
        fvec3_normalize(&ray.direction, &ray.direction);

        struct sphere sphere = {
                .origin = {
                        .x = 3.0,
                        .y = 0.0,
                        .z = 5.0
                },
                .radius = 3.0
        };

        struct intersect intersect;
        if (ray_intersect_with_sphere(&intersect, &ray, &sphere)) {
                printf("sphere intersection point: ");
                fvec3_print(&intersect.point);
                printf("sphere intersection normal: ");
                fvec3_print(&intersect.normal);
                printf("u=%f, v=%f\n", intersect.u, intersect.v);
        }

        struct plane plane = {
                .normal = {
                        .x = 1.0,
                        .y = 0.0,
                        .z = 0.0
                }, .d = -7.0
        };

        ray = (struct ray) {
                .origin = {
                        .x = 2.0,
                        .y = 3.0,
                        .z = 4.0
                }, .direction = {
                        .x = 0.577,
                        .y = 0.577,
                        .z = 0.577
                }
        };

        if (ray_intersect_with_plane(&intersect, &ray, &plane)) {
                printf("plane intersection point: ");
                fvec3_print(&intersect.point);
                printf("plane intersection normal: ");
                fvec3_print(&intersect.normal);
                printf("u=%f, v=%f\n", intersect.u, intersect.v);
        }

        return 0;
}
