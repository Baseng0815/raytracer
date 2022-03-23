#include "raytracer.h"

#include "ray.h"

#include <stdio.h>

void raytracer_render(const struct scene*, int sw, int sh, int ww, int wh)
{
        /* pixel width and height in world coordinates */
        double pw  = sw / (double)ww;
        double ph = sh / (double)wh;
        int swh = sw / 2;
        int shh = sh / 2;

        for (int x = -swh; x < swh; x++) {
                for (int y = -shh; y < shh; y++) {
                        /* generate ray through pixel center */
                        double wx = x / pw + (pw * 0.5);
                        double wy = y / ph + (ph * 0.5);

                        struct ray ray;
                        ray.direction.x = wx;
                        ray.direction.y = wy;
                        ray.direction.z = 1.0f;
                        fvec3_normalize(&ray.direction, &ray.direction);

                        ray.origin.x = 0.0;
                        ray.origin.y = 0.0;
                        ray.origin.z = 0.0;
                }
        }
}
